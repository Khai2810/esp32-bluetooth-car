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
#define IN1 4
#define IN2 2
#define ENA 33
#define PWMCHANEL0 0

#define IN3 18
#define IN4 19
#define ENB 32
#define PWMCHANEL1 1
MotorDC motorLeft(ENB, IN3, IN4, PWMCHANEL1);
MotorDC motorRight(ENA, IN1, IN2, PWMCHANEL0);

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

MotorApp car(motorLeft, motorRight);

unsigned char buffer[BUFFER_SIZE];
CircleBuffer circleBuffer(buffer);

std::string receiveByte;
uint8_t type;
uint8_t intensity;

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue();
    receiveByte = value;

    if (value.length() > 0)
    {
      Serial.print("Nhan du lieu BLE: ");

      // In từng ký tự
      for (int i = 0; i < value.length(); i++)
      {
        uint8_t byte = (uint8_t)value[i];
        circleBuffer.Enqueue(byte);
        Serial.print(value[i]);
      }
      Serial.println();
    }
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

int ParseSpeed(const char *cmd, uint8_t &type, uint8_t &intensity)
{
  type = cmd[0];
  intensity = 0;

  for (int i = 1; cmd[i] >= '0' && cmd[i] <= '9'; i++)
  {
    intensity = intensity * 10 + (cmd[i] - '0');
  }

  if (intensity > 100)
    intensity = 100;
}

void ControlMotor()
{
  ParseSpeed(receiveByte.c_str(), type, intensity);
  // car.SetSpeed(intensity);
  Serial.print(intensity);
  Serial.println();
  Serial.print(type);
  if (type == 'T')
  {
    if (intensity > 50)
    {
      car.MoveRight();
    }
    else if (intensity < 50)
    {
      car.MoveLeft();
    }
  }
  else if (type == 'G')
  {
    if (intensity == 0)
    {
      car.Stop();
    }
    else if (intensity == 2)
    {
      car.MoveBackward();
    }
    else if (intensity == 6)
    {
      car.MoveForward();
    }
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
  // HandleCommand();
  // car.MoveForward();
  // int speed = ParseSpeed(receiveByte.c_str());
  // car.SetSpeed(speed);
  // if (SerialBT.available())
  // {
  //     char incomingChar = SerialBT.read();
  //     Serial.print("Received: ");
  //     Serial.println(incomingChar);

  //     // Car control logic based on incomingChar
  //     switch (incomingChar)
  //     {
  //     case 'F': // Forward
  //         car.MoveForward();
  //         break;
  //     case 'B': // Backward
  //         car.MoveBackward();
  //         break;
  //     case 'L': // Left
  //         car.MoveLeft();
  //         break;
  //     case 'R': // Right
  //         car.MoveRight();
  //         break;
  //     case 'S': // Stop
  //         car.Stop();
  //         break;
  //     default:
  //         break;
  //     }
  // }
  delay(5);
}