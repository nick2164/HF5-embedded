#include "APIHTTPRequestHandler.h"
#include "MbedJSONValue.h"
#include "mbed.h"
#include "string"

#ifndef ROTOR_LoginHandler_H
#define ROTOR_LoginHandler_H

class loginHandler
{
private:
    std::string token;              // This is the token, that othHTTP Requests needs.
    std::string identifier = "LOL"; // This is the identifier that

public:
    int login();
    std::string getToken();
};
#endif