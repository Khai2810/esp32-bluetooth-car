#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include "MotorUtils.h"

class MotorControl
{
  // protected:
  //   virtual void MotorInit() = 0;

protected:
  //   MotorID motorID;
  //   MotorState motorState;
  //   MotorDirection motorDir;

  int speed;
  int pinEnable;
  int pinIN1;
  int pinIN2;
  int pwmChannel;

public:
  MotorControl(int en, int in1, int in2) : speed(0), pinEnable(en), pinIN1(in1), pinIN2(in2)
  {
  }
  // virtual void MotorEnable() = 0;
  virtual void MotorInit() = 0;
  virtual void MotorSetSpeed(int s) = 0;
  // virtual void MotorSetState() = 0;
  // virtual void MotorGetState() = 0;
  virtual void MotorSetDirection(MotorDirection dir) = 0;
  virtual void MotorStop() = 0;
};

#endif