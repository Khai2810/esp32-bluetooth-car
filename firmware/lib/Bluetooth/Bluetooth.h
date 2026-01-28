#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "Command.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>

class Bluetooth : public BLECharacteristicCallbacks
{
private:
  CircleBuffer &buffer;

public:
  void Init();
  // Bluetooth() {}
  Bluetooth(CircleBuffer &buff) : buffer(buff) {}
  void onWrite(BLECharacteristic *pCharacteristic);
};
#endif