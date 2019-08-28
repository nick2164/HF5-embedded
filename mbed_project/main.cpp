/**
 * @file main.cpp
 * @author Nicki Bo Otte (nick2164@edu.sde.dk)
 * 
 * @version 0.1
 * @date 2019-08-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "loginHandler.h"
#include "sMotorHandler.h"

int main()
{
    // Handle login. If it doesn't work, then it will try again after 4 seconds.
    loginHandler loginHandler;
    while (loginHandler.login() != 0)
    {
        loginHandler.login();
        wait(4);
    }

    // Gather token from login attempt
    std::string token = loginHandler.getToken();

    // Use token, to get the status of the rotation, for this device.
    sMotorHandler _sMotorHandler(token);

    // Run in loop
    while (1)
    {
    }
}
