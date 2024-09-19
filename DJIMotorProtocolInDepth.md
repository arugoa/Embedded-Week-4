# DJIMotor Protocol

### DJIMotor-side

On the motor class side, we store all existing motors in a 3D Array, and it is organized as such:

![](assets/allMotors.png)

The first index refers to which BUS the motor is in. The nucleo, the board we use, can support two CAN busses, and we use both of these busses in normal use. The second index is for the sendIDindex, as in, which ID are we sending to.

The motors send to one of 3 adresses, depending on a motor's true ID. If you'll remember earlier, the true ID of a M3508 or M2006 is the same as its ID, but the true ID of a GM6020 is its normal ID + 4. A Motor with a true ID of 1-4 is sent its data to the adress `0x200`. 5-8 is sent in the ID `0x1FF`, and 9-11 (Motor 12 cannot exist) is sent in the ID `0x2FF`. From there, the third index refers to where in that message the motor lies.

It works like this, say we have four motors, IDs 1-4, and they all have unique data. To make them move, we send all four of them data at the same time, through the adress 0x200. We send 8 bytes of data, and the data is paired up into 4 sets of two bytes, and each motor takes a pair as a 16 bit integer.

### Motor-specific

Now, one of these int16s will tell a motor what power to go at, as a number from -16384 to 16383. This is defined by the motor's procotol. In one full frame however, we have the aforementioned 8 bytes, paired up into 4 int16s, controlling four motors at a time, all sent to one adress.

Below is the representation of the data in one frame of data

![](assets/oneframe.jpg)

In this frame, we are telling Motor 1 to give it 1301 power, Motor 2 to give -5012, Motor 3 to give 570, and Motor 4 to give -10000. One more thing to keep in mind is that from stop, a motor will generally need about 1k to overcome static friction and begin moving, and after which that value can be lowered as it only needs to maintain movement, not begin it.
