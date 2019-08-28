/**
 * @file APIHTTPRequestHandler.cpp
 * @author Nicki Bo Otte (nick2164@edu.sde.dk)
 * 
 * @version 0.1
 * @date 2019-08-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "APIHTTPRequestHandler.h"

/**
 * Construct a new APIHTTPRequestHandler::APIHTTPRequestHandler object
 */
APIHTTPRequestHandler::APIHTTPRequestHandler()
{
    if (ethernetHandler::getNetwork() == 0)
    {
        ethernetHandler::connectToInterface();
    }
}

/**
 * This method will create a HTTP Post request, and send it to a given endpoint, 
 * with a given body, expected to be JSON.
 * 
 * @param std::string endpoint
 * @param std::string json
 * @return HttpResponse* 
 */
HttpResponse *APIHTTPRequestHandler::doPOSTRequest(std::string endpoint, std::string json)
{
    NetworkInterface *network = ethernetHandler::getNetwork();

    HttpRequest request(network, HTTP_POST, (host + ":8080" + endpoint).c_str());
    request.set_header("Content-Type", "application/json");

    return request.send(json.c_str(), json.size());
}

/**
 * This method will create a HTPP Get request, and send it to a given endpoint.
 * 
 * @param std::string endpoint
 * @return HttpResponse* 
 */
HttpResponse *APIHTTPRequestHandler::doGETRequest(std::string endpoint)
{
    NetworkInterface *network = ethernetHandler::getNetwork();
    HttpRequest request(network, HTTP_GET, (host + ":8080" + endpoint).c_str());

    return request.send();
}

/**
 * This metod will read a HttpResponse, and printout a valid response,
 * based on the response code
 * 
 * @param HttpResponse *response
 */
void APIHTTPRequestHandler::readResponseAloud(HttpResponse *response)
{
    printf("[NOTICE] Response: ");

    switch (response->get_status_code())
    {
    case 200:
        printf("Success");
        break;
    case 201:
        printf("Created");
        break;
    case 204:
        printf("No Content");
        break;
    case 400:
        printf("Bad request");
        break;
    case 401:
        printf("Unauthorized");
        break;
    case 403:
        printf("Forbidden");
        break;
    case 404:
        printf("Forbidden");
        break;
    default:
        printf("response code:%i\r\n", response->get_status_code());
        break;
    }
    printf("\r\n");
}