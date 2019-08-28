#include "EthernetInterface.h"
#include "Thread.h"
#include "mbed.h"

#ifndef ROTOR_EthernetHandler_H
#define ROTOR_EthernetHandler_H

class ethernetHandler
{
private:
    Thread thread;

public:
    static int connectToInterface();
    static NetworkInterface *getNetwork();
};
#endif