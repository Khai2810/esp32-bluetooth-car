#include <Arduino.h>
#include <BluetoothSerial.h>
#include "MotorControl.h" // Include the motor header
#include "MotorDC.h"      // Include the motor header
#include "MotorApp.h"     // Include the motor header
#include "Command.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// BluetoothSerial SerialBT;
#define INA1 4
#define INA2 2
#define ENA 33
#define PWMCHANEL0 0

#define INB1 18
#define INB2 19
#define ENB 32
#define PWMCHANEL1 1
MotorDC motorLeft(ENB, INB1, INB2, PWMCHANEL1);
MotorDC motorRight(ENA, INA1, INA2, PWMCHANEL0);

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

MotorApp car(motorLeft, motorRight);

unsigned char buffer[BUFFER_SIZE];
CircleBuffer circleBuffer(buffer);

std::string receiveByte;
uint8_t type;
uint8_t intensity;

volatile bool hasNewData = false;

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic) override
  {
    std::string value = pCharacteristic->getValue();

    if (value.empty())
      return;

    // Copy an toàn sang string ASCII
    receiveByte.assign(value.begin(), value.end());
    hasNewData = true;
  }
};

Command command(circleBuffer);

void HandleCommand()
{
  if (!command.ValidatePackage())
  {
    return;
  }
  package_t frame = command.ReturnFrame();
  // AA 00 01
  if (frame.command == FORWARD)
  {
    car.MoveForward();
  }
  else if (frame.command == REVERSE)
  {
    car.MoveBackward();
  }
}

void ParseSpeed(const char *cmd, uint8_t &type, uint8_t &intensity)
{
  if (cmd == nullptr || cmd[0] == '\0')
  {
    type = 0;
    intensity = 0;
    return;
  }

  type = cmd[0];
  intensity = 0;

  for (int i = 1; cmd[i] >= '0' && cmd[i] <= '9'; i++)
  {
    intensity = intensity * 10 + (cmd[i] - '0');
  }

  if (intensity > 100)
    intensity = 100;
  intensity *= 2;
}

void ControlMotor()
{
  if (!hasNewData)
    return;
  hasNewData = false;

  ParseSpeed(receiveByte.c_str(), type, intensity);

  Serial.print("Type: ");
  Serial.println((char)type);
  Serial.print("Intensity: ");
  Serial.println(intensity);

  if (type == 'T')
  {
    if (intensity > 100)
      car.MoveRight();
    else if (intensity < 100)
      car.MoveLeft();
    else
    {
      car.Stop();
    }
  }
  else if (type == 'G')
  {
    if (intensity == 0)
      car.Stop();
    else if (intensity == 2)
      car.MoveBackward();
    else if (intensity == 6)
      car.MoveForward();
  }
  else if (type == 'S')
  {
    car.SetSpeed(intensity);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("MyESP32");

  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);

  // Gán callback
  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello World says ESP32");

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("BLE ready! Waiting for data...");
}

void loop()
{
  ControlMotor();
  delay(5);
}