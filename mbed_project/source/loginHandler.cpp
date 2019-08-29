/**
 * @file loginHandler.cpp
 * @author Nicki Bo Otte (nick2164@edu.sde.dk)
 * 
 * @version 0.1
 * @date 2019-08-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "loginHandler.h"

/**
 * This method will form a form a post request so that, a token can
 * be returned from the API. This token will then be stored in getToken()
 * for others to use.
 * 
 * @return int 
 *      0 = Token is gathered and saved.
 *      -1 = Something went wrong.
 */
int loginHandler::login()
{
    // Make HTTP request to gather Token
    APIHTTPRequestHandler HTTPRequest;
    std::string json = "{\"identifier\": \"" + this->identifier + "\"}";
    HttpResponse *response = HTTPRequest.doPOSTRequest("\/token", json);
    HTTPRequest.readResponseAloud(response);

    if (response->get_status_code() == 200)
    {
        // Parse return data and save the token
        MbedJSONValue jsonParser;
        parse(jsonParser, response->get_body_as_string().c_str());
        token = jsonParser["token"].get<std::string>();
        return 0;
    }
    else
    {
        return -1;
    }
}

/**
 * This getter will return the token, which is gathered in the constructor.
 * 
 * @return string 
 */
string loginHandler::getToken()
{
    return token;
}