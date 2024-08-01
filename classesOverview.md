# Classes Overview

### DJIMotor

DJIMotor is the class we use to interface with motors. It both sends data to the motors and recieves feedback from them, but the appropriate static methods `s_sendValues()` and `s_getFeedback()` need to be called occasionally. `s_sendValues()` needs to be called less often however, or it will interfere with feedback. Once a motor is constructed according to physical specs and physically set settings, we can make it move with included functions. Docs here: [TR-mbed: DJIMotor Class Reference](https://triton-robotics.github.io/TR-mbed/classDJIMotor.html)

### Chassis

The Chassis class is what handles main robot movements. It takes the four chassis motors and drives them using mecanum code, taking in an x, y, and rotational value. It also has code to handle driving relative to the turret angle, and driving without exceeding the power limit. Docs here: [TR-mbed: Chassis Class Reference](https://triton-robotics.github.io/TR-mbed/classChassis.html)

### PID

The PID class is our main controls class. We use it for all the motor's position and speed control. We also use it for power limiting the chassis. It is a good general purpose controls algorithm that you can use in a good many scenarios. Docs here: [TR-mbed: PID Class Reference](https://triton-robotics.github.io/TR-mbed/classPID.html)

### Remote

The Remote class is how we get remote data to use on the robot. To update this data, we have to call `remoteRead()` every so often. The remote reciever goes through an inverter to the nucleo, at which point it can be read as UART at a baud of 100000. Docs here: [TR-mbed: Remote Class Reference](https://triton-robotics.github.io/TR-mbed/classRemote.html)

### Referee

The Referee clas is how we interface with the Referee system. We need to call the `refereeThread()` function every so often to update its values. However, it is a laggy function, so calling it too often slows down other code. This is why we call it every 5 of the inner loop (About 50ms). Docs here: [TR-mbed: Referee Class Reference](https://triton-robotics.github.io/TR-mbed/classReferee.html)

### TRMutex

TRMutex is a custom print class that we have, designed to print things asycnchronously and threaded, so that there are no issues with slowing down real robot code with debug statements. The way to use TRMutex prints in main robot code is to simply replace all `printf` statements with `printff`.  Docs here: [TR-mbed: TRMutex Class Reference](https://triton-robotics.github.io/TR-mbed/classTRMutex.html)

### CANHandler

The CANHandler handles all low level communications with the CAN line. The DJIMotor give it messages to send, and recieves messages from its buffer, and it handles the rest. Docs here: [TR-mbed: CANHandler Class Reference](https://triton-robotics.github.io/TR-mbed/classCANHandler.html)

### BNO055

The BNO055 is the IMU that we use for the robots. It's used to stabilize the turret to a world-relative angle, because the stability of the turret is what matters most when aiming. Docs here: [TR-mbed: BNO055 Class Reference](https://triton-robotics.github.io/TR-mbed/classBNO055.html)

### Jetson

The Jetson class has methods and functions to read from and write to the Jetson. We get X and Y turret data, and send it movement and team data. Docs here: [TR-mbed: Jetson Class Reference](https://triton-robotics.github.io/TR-mbed/classJetson.html)

# Example Code

If you'd like to look at some example code that uses most of these, you can find that [here](baseCodeExample.md)
