#include "APIHTTPRequestHandler.h"
#include "MbedJSONValue.h"
#include "Thread.h"
#include "mbed.h"
#include "steppermotor.h"

#ifndef ROTOR_sMotorHandler_H
#define ROTOR_sMotorHandler_H

class sMotorHandler
{
private:
    bool clockwise;
    Thread thread;
    std::string token;
    void directionChooser();

public:
    sMotorHandler(std::string token);
};
#endif;