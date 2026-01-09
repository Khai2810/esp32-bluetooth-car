#include "MotorControl.h"
#include "MotorApp.h"
#include "MotorUtils.h"

// void ErrorHandling();
// void RecieveCommand();
// void SendACK();
// void MoveForward();
// void MoveAfter();
// void MoveRight();
// void MoveLeft();
// void TurnOn();
// void TurnOff();
void MotorApp::MoveForward()
{
  motorRight.MotorSetDirection(FORWARD);
  motorLeft.MotorSetDirection(FORWARD);
}

void MotorApp::MoveBackward()
{
  motorLeft.MotorSetDirection(REVERSE);
  motorRight.MotorSetDirection(REVERSE);
}

void MotorApp::MoveRight()
{
  motorLeft.MotorSetDirection(FORWARD);
  motorRight.MotorStop();
}

void MotorApp::MoveLeft()
{
  motorRight.MotorSetDirection(FORWARD);
  motorLeft.MotorStop();
}

void MotorApp::SetSpeed(int speed)
{
  motorRight.MotorSetSpeed(speed);
  motorLeft.MotorSetSpeed(speed);
  // delay(1000);
}

void MotorApp::Stop()
{
  motorLeft.MotorStop();
  motorRight.MotorStop();
}