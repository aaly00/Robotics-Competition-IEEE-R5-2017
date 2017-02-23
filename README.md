Welcome to PVAMU IEEE Robotics Team Build 2017!
===================================

This repository will serve as a documentation for the robot build for the IEEE R5 robotics competition 2017.
[**Link to the competition rules**](https://drive.google.com/file/d/0Byoc_-AOKdM3Y2l4aGluVUU1c2M/view?usp=sharing)

----------
##Competition Description & Rules##
-----------
Motivation:
  :	The objective of the competition is to demonstrate the use of an autonomous robot on the surface to map a tunnel and investigate “buried caches” at the tunnel endpoints. The game field simulates a tunnel containing infrastructure such as steel cables or rails for material transport and electrical conductors for lighting or communications. Surface obstacles and anomalies represent typical operational challenges.

###Rules###
Playing Field:
  :	The Game Field base is 1⁄2” x 8’ x 8’ MDF panels. Centered on top of the MDF is a 3/16” x 7’ x 7’ pegboard. Forty-nine 2”x1’x1’ “grid blocks” cut from sheets of Extruded Polystyrene (XPS) insulation are Page 2 of 11 V4, Nov 5, 2016 arranged in a 7 x 7 grid on the pegboard. The playing field will be then covered in whole by a 1⁄4” thick sheet of acrylic glass which will create a surface over the grid blocks. The robot will navigate on the acrylic surface. Acrylic is employed to enhance audience viewing. To minimize the sole use of vision for subsurface mapping, sheets of paper will be interspersed between the grid blocks and acrylic. Any component may vary in color or physical properties. A minimum of seven contiguous grid blocks under the Game Field surface will be removed to form the tunnel. The endpoints will NOT be located on the same side of the Game Field. Infrastructure emulating  winch cables and power lines will run inside the tunnel from endpoint to endpoint. The winch cables are emulated by 16-Gauge galvanized steel wire. The power cables will be emulated by a plastic shield incandescent trouble light connected to a 25’ 16/3 extension cord connected to the RMEC 120V 60Hz. Additional grid blocks may be removed to form “dead ends” connected to the OT. A dead end will not contain infrastructure. Bonus points will be awarded for correctly mapping dead ends.  “Buried” caches with a removable lid are located in the Game Field perimeter. Each of the two tunnel endpoints will include a cache. A single white die with black points (Cache Die) will be located in the bottom of each OT endpoint cache. One or more obstructions will be placed on the surface to emulate operational challenges. These surface obstructions will consist of grid blocks removed to form tunnels. Only one grid block will be used per obstruction. The robot START/STOP location will always occupy grid location A7 and serve as a geographic reference for displaying and judging a map. A7 will not contain any portion of the OT or a dead end and it will not contain a buried cache.
  
  ![Field Grid Location Reference](http://i.imgur.com/U3f8P9k.png)


 ![Playing Field](http://i.imgur.com/rrfTyYz.png)
	Figure 2: Playing field (A7 is starting location)

>**Robot Requirements:**
 
 > - Autonomous Operation - No communication with the robot after placement in the Quarantine Area. Communication may begin after the robot is removed from the Game Field after a Round.
> -  Size – While occupying the START/STOP location (A7) the robot must fit inside a 12” square cube. All inner cube edges are 12 (+/-0.25)” and all angles are 90 (+/-1) degree.
> -  Weight – Must weigh 30.0 pounds or less. Robots over 30.0 pounds may, at the discretion of the Head Judge, be disqualified without appeal.
> -  Chemicals or explosives – Explosives and volatile liquids are not permitted. Chemical batteries are allowed but only if used correctly and  with appropriate safety and handling. 
> -  Mapping Display (MD) Requirement - an 8x8 RGB LED pixel array firmly attached to the uppermost horizontal surface of the robot.
> -  Die Point Display (DPD) Requirement - a red 7-segment single digit display firmly attached to the uppermost horizontal surface of the robot and adjacent to the MD.
> -  The robot must have a Red “STOP” button and Green “GO” button easily accessible on the uppermost horizontal surface of the robot. Each button will be labeled STOP or GO using Arial Font, Regular Style, Size 20 or larger.
> -   A single corner LED on the MD will be designated as the Yellow “Robot Ready” Light. This LED will also map START/STOP grid location A7. The OT map must be correctly referenced to the START/STOP grid location A7. For this reason, the Yellow “Robot Ready” Light must remain continuously lit until the Scoring Judge asks the robot to be removed from the Game Field.

For more rules and requirements please reference the competition handbook [**competition rules**](https://drive.google.com/file/d/0Byoc_-AOKdM3Y2l4aGluVUU1c2M/view?usp=sharing)
 
 ----------
##Our Approach##

####Abstract:#####
 : In our approach to the problem we decided to create a land robot. We decided to go with a differential drive based robot with two caster wheels due to the stability it offers. We will be using multiple controllers, and SOC computers to execute the different functionalities of the robot. In our approach, we will also try to make our design decisions in every aspect as modular as possible, and use sensor, and controller packages to make the system as easy to troubleshoot as possible.

####Drive: ####
: As mentioned earlier, We decided to proceed with the differential drive control method for multiple reasons. 

![Differential drive](http://i.imgur.com/F9FaJ1Q.png)
Figure 3:  Differential drive diagram.
> - Differential Drive requires only two motors which makes power consumption lower in general than having to drive more than two motors.
> - When driving a robot in differential drive creating a closed feedback (PID) loop becomes easier than having to deal with a closed feedback loop for four motors to move autonomously.
> - Design, mechanical construction and control algorithm can never get any simpler than this driving technique, and the concept can be incorporated in almost any kind of robots including legged robots.
> - A problem with the differential drive is that the robot does not drive as expected. It neither drives along a straight line nor turn exactly at expected angles, especially when we use DC motors. This is due to difference in the number of rotations of each wheel in a given amount of time. To handle this problem, we need to add correction factor to the motor speed which will be discussed in our choice for the motor controller.

####Wheels, and motor's choice:####
: **Force (exerted by the wheel on the surface) x radius (of the wheel) = torque (of the motor)** If we need to exert a high force,since the robot may be heavy, we need to increase either the torque or decrease the radius of the wheel. In order to achieve the same forward speed for the robot, smaller wheels have to rotate faster. Using [society of robots guide](http://www.societyofrobots.com/mechanics_dynamics.shtml) on amount of torque needed for a particular differential drive robot given our estimated mass, and [wheels choice](https://www.pololu.com/product/1433), the torque needed is around 170 oz-in so we decided to go with the pololu [70:1 Metal Gearmotor 37Dx70L mm with 64 CPR Encoder](https://www.pololu.com/product/2825) since it will offer best combination of crusing speed and torque.

####Controllers:####




