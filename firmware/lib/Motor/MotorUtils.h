#ifndef MOTORUTILS_H
#define MOTORUTILS_H

#include <Arduino.h>

enum MotorID
{
    MOTOR_1,
    MOTOR_2
};

enum MotorState
{
    STOP,
    RUN
};

enum MotorDirection
{
    FORWARD,
    REVERSE
};

enum CommandDirection
{
    COM_FORWARD,
    COM_REVERSE,
    COM_RIGHT,
    COM_LEFT
};

// typedef struct MotorMessage
// {
//     MotorID motorID;
//     MotorState motorState;
//     MotorDirection motorDir;
//     int speed;
// };

#endif