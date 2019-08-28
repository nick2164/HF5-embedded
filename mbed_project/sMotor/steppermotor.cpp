#include "steppermotor.h"
#include "sMotor.h"

///Sets pins for steppermotor
sMotor motor(A0, A1, A2, A3);

/**
* This is the constructor which sets the step speed and number of steps.
* @author Nikolaj M. & Mathias R.
* @param stepSpeed stepspeed to use for steppermotor
* @param numStep number of steps to step with steppermotor
* @date 24/1/2019
*/
steppermotor::steppermotor(int stepSpeed, int numStep)
{
    setStepSpeed(stepSpeed);
    setNumStep(numStep);
}

/**
* This method will be used to set the variable step_speed.
* @author Nikolaj M. & Mathias R.
* @param stepSpeed value to be set in step_speed
* @date 24/1/2019
*/
void steppermotor::setStepSpeed(int stepSpeed)
{
    this->step_speed = stepSpeed;
}

/**
* This method will be used to get the variable step_speed.
* @author Nikolaj M. & Mathias R.
* @return step_speed value to caller
* @date 24/1/2019
*/
int steppermotor::getStepSpeed()
{
    return this->step_speed;
}

/**
* This method will be used to set the variable numstep.
* @author Nikolaj M. & Mathias R.
* @param stepSpeed value to be set in step_speed
* @date 24/1/2019
*/
void steppermotor::setNumStep(int numStep)
{
    this->numstep = numStep;
}

/**
* This method will be used to get the variable numstep.
* @author Nikolaj M. & Mathias R.
* @return numstep value to caller
* @date 24/1/2019
*/
int steppermotor::getNumStep()
{
    return this->numstep;
}

/**
* This method will be used to get call funtion that makes steppermotor spin clockwise in sMotor lib.
* @author Nikolaj M. & Mathias R.
* @date 24/1/2019
*/
void steppermotor::open()
{
    motor.step(this->getNumStep(), 0, this->getStepSpeed());
}

/**
* This method will be used to get call funtion that makes steppermotor spin anticlockwise in sMotor lib.
* @author Nikolaj M. & Mathias R.
* @date 24/1/2019
*/
void steppermotor::close()
{
    motor.step(this->getNumStep(), 1, this->getStepSpeed());
}