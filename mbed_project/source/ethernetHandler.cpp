/**
 * @file ethernetHandler.cpp
 * @author Nicki Bo Otte (nick2164@edu.sde.dk)
 * 
 * @version 0.1
 * @date 2019-08-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "ethernetHandler.h"

nsapi_size_or_error_t result;
NetworkInterface *net;

/**
 * Getter for NetworkInterface pointer
 * 
 * @return NetworkInterface* 
 */
NetworkInterface *ethernetHandler::getNetwork()
{
    return net;
}

/**
 * This method will create the network interface, and fill out 
 * the Net property, so that other code can refer to it.
 * 
 * @return nsapi_error_t 
 */
nsapi_error_t ethernetHandler::connectToInterface()
{
    printf("Connecting to network\r\n");
    net = NetworkInterface::get_default_instance();
    result = net->connect();
    if (result != 0)
    {
        printf("[WARNING] Error! net->connect() returned: %i\r\n", result);
    }
    else
    {
        printf("[NOTICE] Success! Your IP is: %s\r\n", net->get_ip_address());
    }

    return result;
}