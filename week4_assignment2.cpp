//STARTER 
//THIS EXERCISE IS TO BE DONE AND THEN RUN IN REAL LIFE ON A ROBOT
//YOU WILL NOT BE ABLE TO COMPILE THIS UNLESS YOU SET UP THE BUILD ENVIRONMENT
#include "main.h"

DigitalOut led(L26);
DigitalOut led2(L27);
DigitalOut led3(L25);

I2C i2c(I2C_SDA, I2C_SCL);

//DEFINE MOTORS, ETC
const int RPM_MAX = 9000;
const int REMOTE_MAX = 660;
const int RPM_REMOTE_RATIO = RPM_MAX / REMOTE_MAX;

DJIMotor* DJIMotor::s_allMotors[2][3][4];
bool DJIMotor::s_motorsExist[2][3][4];
Remote remote;

DJIMotor* frontleft = new DJIMotor(1, CANHandler::CANBus::CANBUS_1, motorType::M3508, "FL");

DJIMotor* frontright = new DJIMotor(2, CANHandler::CANBus::CANBUS_1, motorType::M3508, "FR");

DJIMotor* backleft = new DJIMotor(3, CANHandler::CANBus::CANBUS_1, motorType::M3508, "BL");

DJIMotor* backright = new DJIMotor(4, CANHandler::CANBus::CANBUS_1, motorType::M3508, "BR");


int main(){

    //assigning can handler objects to motor class.
    DJIMotor::s_setCANHandlers(&canHandler1,&canHandler2, false, false); 

    //getting initial feedback.
    DJIMotor::s_getFeedback();

    unsigned long loopTimer_u = us_ticker_read();
    unsigned long timeEnd_u;
    unsigned long timeStart_u;

    int refLoop = 0;

    //DEFINE PIDs AND OTHER CONSTANTS

    while(true){ //main loop
        timeStart_u = us_ticker_read();

        //inner loop runs every 25ms
        if((timeStart_u - loopTimer_u) / 1000 > 25) { 
            loopTimer_u = timeStart_u;
            led = !led; //led blink tells us how fast the inner loop is running

            if (refLoop >= 5) { //ref code runs 5 of every inner loop, 
                refLoop = 0;
                refereeThread(&referee);
            }
            refLoop ++;

            remoteRead(); //reading data from remote
        
            //MAIN CODE
            int flspeed, frspeed, blspeed, brspeed = 0, 0, 0, 0;

            flspeed += ((remote.leftY() + remote.leftX() + remote.rightX()) * RPM_REMOTE_RATIO) % RPM_MAX;

            frspeed += ((-remote.leftY() + remote.leftX() + remote.rightX()) * RPM_REMOTE_RATIO) % RPM_MAX;

            blspeed += ((remote.leftY() - remote.leftX() + remote.rightX()) * RPM_REMOTE_RATIO) % RPM_MAX;

            brspeed += (( - remote.leftY() - remote.leftX() + remote.rightX()) * RPM_REMOTE_RATIO) % RPM_MAX;

            frontleft->setSpeed(flspeed);
            frontright->setSpeed(frspeed);
            backleft->setSpeed(blspeed);
            backright->setSpeed(brspeed);

            //MOST CODE DOESNT NEED TO RUN FASTER THAN EVERY 25ms

            timeEnd_u = us_ticker_read();

            DJIMotor::s_sendValues();
        }

        //FEEDBACK CODE DOES NEED TO RUN FASTER THAN 1MS
        //OTHER QUICK AND URGENT TASKS GO HERE

        DJIMotor::s_getFeedback();
        ThisThread::sleep_for(1ms);
    }
}
