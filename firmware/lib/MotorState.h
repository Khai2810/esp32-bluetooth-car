#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include "MotorUtils.h"

class MotorSM
{
public:
    void SwitchOffOn();
    void SwitchIdleOn();
    void SwitchOnOff();
    void SwitchOnIdle();
    void SwitchIdleOff();
};

#endif