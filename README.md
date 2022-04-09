This repo contains my Arduino projects, peace-v-

---Blink---
	"test arduino board"

---Test_motor---
	"test hall encoder of motor GM25"
	
	-GM25:  (2 pin -> L298N, 4 pin -> UNO) x 2
	-L298N: 2 pin -> Battery, (3 pin -> UNO) x 2
	(UNO-GND <-> L298N-GND)
	
---PID--- 
	"tunning PID (speed and pos) for GM25 motors"
	
	- Only 2 digits after dot: ie. 4.9 0.01
	- Kp: inc until completely lost stable (full spikes) -> dec to "few spikes"
	- Kd: cut spikes, response more "narrow" (dec occilates)
	- Kp: remove e, but occilates.
	- OBSERVE yourself.
	
---RF24---
	"remote control motor by keyboard - sub /cmd_vel topic"
		
---ROS-GM25-odom---
	"publish odometry to ROS"
	
	- first bug: odom message too big
	- biggest bug caused by hardware: use 2 power supply for Mega board at the 
	same time	-> NO, it is not! 2 power supply is OK.
	
	- biggest bug is baud too small (57600), change baud to 600800 solved the problem

