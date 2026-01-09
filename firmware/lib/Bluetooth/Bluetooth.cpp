#include "Bluetooth.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>
#define DEVICE_NAME "MYESP32"

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void Bluetooth::onWrite(BLECharacteristic *pCharacteristic)
{
  std::string value = pCharacteristic->getValue();

  for (size_t i = 0; i < value.length(); i++)
  {
    unsigned char byte = static_cast<unsigned char>(value[i]);
    buffer.Enqueue(byte);
  }
}

void Bluetooth::Init()
{
  BLEDevice::init(DEVICE_NAME);
  BLEServer *server = BLEDevice::createServer();
  BLEService *service = server->createService(SERVICE_UUID);
  BLECharacteristic *rxCharacteristic = service->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_WRITE);

  // txCharacteristic = service->createCharacteristic(
  //     CHARACTERISTIC_UUID,
  //     BLECharacteristic::PROPERTY_NOTIFY);
  rxCharacteristic->setCallbacks(new Bluetooth());

  service->start();
  BLEAdvertising *adv = BLEDevice::getAdvertising();
  adv->addServiceUUID(SERVICE_UUID);
  adv->start();
}