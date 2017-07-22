# MonaMk2
Library for the Mona mk2

A c++ library (Arduino) writen by Ben Bird for a differential drive robot designed by Farshad Arvin at the University of Manchester.

Library can eaily be used to provide low level control of any differential drive robot by simply changing the pin definitions. Your hardware will require encoders connected to interrup pins.

A ros node is included which allows control of the Mona robot (or any other differential drive robot) using the turtlebot turtlesim commands - i.e twist etc. The node will also publish encoder data, which will change based on direction and movement of the wheels. 

A characterisation program is provided which will characterise the drive motors automatically and produce linear, squared and cubic polynomails describing the relationship between motor PWM and wheel linear velocity. 


