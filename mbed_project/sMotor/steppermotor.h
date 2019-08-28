/**
*
* @file steppermotor.h
* @brief make grove steppermotor to turn via analog input.
*
* @author Nikolaj M. & Mathias R.
*
* @date 23/1/2019
*
*-----EXAMPLE-----
*#include "steppermotor.h"
*steppermotor gate(2200, 200);
*
*
*int main() {  
*   gate.open();
*   gate.close();
*}
*-----EXAMPLE-----
**/

//PROGRAM: StepperMotor

#ifndef STEPPERMOTOR
#define STEPPERMOTOR
///StepperMotor CLASS
class steppermotor{
    ///INITIALIZE VARIABLES USED IN CLASS
    private:
        int step_speed;
        int numstep;
    ///FUNCTIONS AND CONSTRUCTOR
    public:
        steppermotor(int stepSpeed, int numStep);
        void setStepSpeed(int stepSpeed);
        int getStepSpeed();
        void setNumStep(int numStep);
        int getNumStep();
        void open();
        void close();
};

#endif