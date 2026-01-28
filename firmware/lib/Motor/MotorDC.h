#ifndef MOTORDC_H
#define MOTORDC_H

#include <Arduino.h>
#include "MotorControl.h"

class MotorDC : public MotorControl
{
    // protected:
    //     void MotorInit() override;

private:
    MotorID motorID;
    MotorState motorState;
    MotorDirection motorDir;

    int speed;
    int pinEnable;
    int pinIN1;
    int pinIN2;
    int pwmChannel;

    void MotorInit();

public:
    MotorDC(int en, int in1, int in2, int pwm) : pinEnable(en), pinIN1(in1), pinIN2(in2), pwmChannel(pwm)
    {
        MotorInit();
    }
    // void MotorEnable() override;
    void MotorSetSpeed(int speed) override;
    // void MotorSetState() override;
    // void MotorGetState() override;
    void MotorSetDirection(MotorDirection dir) override;
    void MotorStop() override;
};

#endif