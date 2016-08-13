# Exercise Bike Project #

**Version:** 1.0  
**Date:** 12 August 2016


This code is to be used on an Arduino Uno Rev3 to control the exercise bike add-on built by Paly Robotics. The project is attached to an exercise bike and adjusts the volume of an audio source based on the pedalling speed.


Magnets of alternating directions are placed around the circumfrence of the exercise bike wheel. They are detected by a latching U1881 hall effect sensor and read by the Arduino. Transfers from LOW to HIGH states are recorded as ticks. Every 2.5 seconds the number of ticks divided by a constant to get a scaled value by which to modify the volume with scaled valued capped at 1. The desired scaling factor, now between 0 and 1, is coverted into a servo angle for a 201 degree HS-322HD servo. The servo is coupled to a L-pad audio attenuator which is connected to a 3.5 mm audio jack and a 3.5 mm audio source. 


For more information about this code or project contact Jonathan Zwiebel at jzwiebel@palyrobotics.com
