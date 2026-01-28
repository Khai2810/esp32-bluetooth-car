#include "MotorDC.h"

#define PWM_FREQ 1000 // 1kHz
#define PWM_RES 8     // 8-bit: 0–255

// void MotorEnable() override;
// void MotorSetSpeed(int speed) override;
// void MotorSetState() override;
// void MotorGetState() override;
// void MotorSetDirection(MotorDirection dir) override;
// void MotorInit() override;

void MotorDC::MotorInit()
{
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  ledcSetup(pwmChannel, PWM_FREQ, PWM_RES);
  ledcAttachPin(pinEnable, pwmChannel);
  ledcWrite(pwmChannel, 0);
  Serial.printf("Init motor: EN=%d CH=%d\n", pinEnable, pwmChannel);
}

void MotorDC::MotorSetDirection(MotorDirection dir)
{
  if (dir == FORWARD)
  {
    digitalWrite(pinIN1, LOW);
    digitalWrite(pinIN2, HIGH);
  }
  else if (dir == REVERSE)
  {
    digitalWrite(pinIN1, HIGH);
    digitalWrite(pinIN2, LOW);
  }
}

void MotorDC::MotorStop()
{
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, LOW);
  ledcWrite(pwmChannel, 0);
}

void MotorDC::MotorSetSpeed(int speed)
{
  speed = constrain(speed, 0, 255);
  ledcWrite(pwmChannel, speed);
}
