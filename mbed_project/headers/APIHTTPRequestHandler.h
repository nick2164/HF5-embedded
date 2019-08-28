#include "ethernetHandler.h"
#include "http_request.h"
#include "mbed.h"
#include "string"

#ifndef ROTOR_APIHTTPRequestHandler_H
#define ROTOR_APIHTTPRequestHandler_H
class APIHTTPRequestHandler
{
private:
    std::string host = "http://10.142.66.159";

public:
    APIHTTPRequestHandler();
    HttpResponse *doPOSTRequest(std::string endpoint, std::string json);
    HttpResponse *doGETRequest(std::string endpoint);
    void readResponseAloud(HttpResponse *response);
};
#endif
