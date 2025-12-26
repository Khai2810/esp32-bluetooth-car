#ifndef MOTORAPP_H
#define MOTORAPP_H

#include <Arduino.h>
#include "MotorUtils.h"

class MotorApp
{
private:
  MotorControl &motorLeft;
  MotorControl &motorRight;

public:
  MotorApp(MotorControl &left, MotorControl &right) : motorLeft(left), motorRight(right)
  {
  }
  // void ErrorHandling();
  // void RecieveCommand();
  // void SendACK();
  void MoveForward();
  void MoveBackward();
  void MoveRight();
  void MoveLeft();
  void Stop();
  void SetSpeed(int speed);
  // void TurnOn();
  // void TurnOff();
};

#endif