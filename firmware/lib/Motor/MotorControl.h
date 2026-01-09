#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include "MotorUtils.h"

class MotorControl
{
  // protected:
  //   virtual void MotorInit() = 0;

  // private:
  //   MotorID motorID;
  //   MotorState motorState;
  //   MotorDirection motorDir;

  //   int speed;
  //   int pinEnable;
  //   int pinIN1;
  //   int pinIN2;

public:
  // MotorControl(int en, int in1, int in2) : pinEnable(en), pinIN1(in1), pinIN2(in2)
  // {
  //   MotorInit();
  // }
  // virtual void MotorEnable() = 0;
  virtual void MotorSetSpeed(int speed) = 0;
  // virtual void MotorSetState() = 0;
  // virtual void MotorGetState() = 0;
  virtual void MotorSetDirection(MotorDirection dir) = 0;
  virtual void MotorStop() = 0;
};

#endif