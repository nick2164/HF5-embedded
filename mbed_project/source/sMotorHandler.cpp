/**
 * @file sMotorHandler.cpp
 * @author Nicki Bo Otte (nick2164@edu.sde.dk)
 * 
 * @version 0.1
 * @date 2019-08-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "sMotorHandler.h"

/**
 * This method will start the gear stepper motor[1], and then decide 
 * which way it's going to turn, based on a get request to the API.
 * 
 * 
 * [1] http://wiki.seeedstudio.com/Gear_Stepper_Motor_Driver_Pack/
 */
void sMotorHandler::directionChooser()
{
    printf("[NOTICE] Thread started in directionChooser.\r\n");

    // Start the stepper motor.
    steppermotor sMotor(2000, 1);

    while (true)
    {
        // Make HTTP request to gather Token
        APIHTTPRequestHandler requestHandler;

        printf("[NOTICE] Asking for decision!\r\n");
        HttpResponse *response = requestHandler.doGETRequest("/device/" + token);
        requestHandler.readResponseAloud(response);

        // Making sure that the numbers of steps are set, for a new run.
        sMotor.setNumStep(50);

        if (response->get_status_code() == 200) // Go for the new data that is gathered via the API.
        {
            // Parse return data and save the token
            MbedJSONValue jsonParser;
            parse(jsonParser, response->get_body_as_string().c_str());
            bool rotateClockwise = jsonParser["rotateClockwise"].get<bool>();

            // Save status of the rotation
            if (this->clockwise != rotateClockwise)
                this->clockwise = rotateClockwise;

            if (rotateClockwise)
            {
                sMotor.open();
            }
            else
            {
                sMotor.close();
            }
        }
        else // Go for the last gathered data, if no response is given.
        {
            if (this->clockwise)
            {
                sMotor.open();
            }
            else
            {
                sMotor.close();
            }
        }
    }
}

/**
 * Construct a new sMotorHandler::sMotorHandler object
 * 
 * @param std::string token
 */
sMotorHandler::sMotorHandler(std::string token)
{

    this->token = token;

    thread.start(callback(this, &sMotorHandler::directionChooser));
}