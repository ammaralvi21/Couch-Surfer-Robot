# Robot-Couch-Surfer-Car
Embedded electronics systems engineering project.

![me](https://github.com/ammaralvi21/Robot-Couch-Surfer-Car/blob/master/Images/Robot%20Car.gif)

The couch surfer robot is designed to navigate around a 1.7m by 0.7m couch starting from a corner on a white surface. Along its route, it interacts with the boxes that are flushed against the couch which come in various sizes. The minimum width of the boxes is 15cm width and 25cm length to account for the size of robot chassis. The couch surfer should autonomously navigates around the object and the count the number of white strips placed adjacent to the boxes. The number of stripes counted correspond to the box number. It then stop at the same white surface it started from. This is all sensor based.

# Component Selection
The perseids Robot Car 4WD Chassis Kit from amazon.ca was used. It included 4 DC Gear motors (TTMotors) and 4xAA battery box for motor power supply which gives us around 6V. The current consumption of those motors is around 200mA at 0.15Nm ~0.60Nm torque.

To drive these motors, we used a two H-Bridge motor driver DRV8833 with 1.2A output per channel. It runs at 2.7 to 10.8 V logic/motor power so therefore it would be able to accept 3.3V PWM signals from the STM32 board.

To sense the distance from the robot to the couch/boxes for navigation, we decided to use three HC-SR04 Ultrasonic sensors. On its trigger input, it accepts a 10us pulse width which sends 8 cycle sonic bursts from the module. On its echo pin, it outputs a pulse width that is proportional to the distance measured (uS / 58 = centimeters). 

In order to uniquely sense white surfaces, we determined an infrared sensor would be a suitable choice. We chose the TCRT5000 infrared sensor module that works at very small distances. It constantly transmitts infrared light and the strength of the reflected light measured determines if the object was black or white. The sensor can be calibrated at certain heights using potentiometer and comparator on the module to provide a digital logic 1 if it detects a dark surface and a logic of 0 if it detected a white surface.

To display the information gathered by the robot, we decided to use a Bluetooth serial monitor. An HC-05 module was selected to wireless transmit our Bluetooth data. The HC-05 has a UART serial interface that can be used to connect to the STM32 board.

# Component quantity and cost
Component Name Quantity Cost: ($)
DRV8833 Dual H-Bridge Motor Driver x1 3.49
HC-SR04 Ultrasonic Sensor x3 5.59
TCRT5000 IR Line Sensor x1 1.99
HC-05 Bluetooth Module x1 13.93
Perseids Robot Car 4WD with Motor x1 22.99
6 x AA Battery holder X1 4.19
8 inch Premium Female/Male Jumper Extension 40pc X1 5.95
Ultrasonic Sensor Acrylic Mounting Bracket X3 4.17
Total: 62.30

# High-Level Block Diagram
A high level block diagram for the connection of the system is shown below.

![me](https://github.com/ammaralvi21/Robot-Couch-Surfer-Car/blob/master/Images/System%20Block%20Diagram.png)

# Detailed Design
Port selection was an important step in our design as certain ports on the STM32VDL were only available for our sensor inputs. Setting ports PA8-11 as alternate functions enabled us to use TIM1 for sending PWM output signals to our H-Bridge Motor Driver. Our Bluetooth module was connected to PB10 since it’s alternate function is USART3. Since our Bluetooth module only needed to transmit data to another device, we only used the TX pin.

A lot of the GPIO pins on our discovery board would only tolerate up to 3.3V inputs and since most of our external components operated in 5V, we looked to the STM32 reference manual to determine which 5V pins were available. A lot of the GPIO pins were also connected externally to the ENEL 384 PCB, and so after carefully considering all of these constraints, we determined which GPIO pins were best for use.

Below is the schematic representation of all the ports used for our system.

![me](https://github.com/ammaralvi21/Robot-Couch-Surfer-Car/blob/master/Images/Schematic%20Diagram.png)

# Robot Navigation Process
In order to conceptualize the process on how the robot would navigate the course and how our main code would flow, we came up with a flow chart in the form of a pseudo state diagram, see figure below. It gave us a logical understanding on how to go about implementing the main application code. The flow of the main function in our application somewhat flows like the chart where each of the nodes represent a while loop that runs until a certain condition has been met. The conditions are sensed inputs that are represented by the flow line.

![me](https://github.com/ammaralvi21/Robot-Couch-Surfer-Car/blob/master/Images/Robot%20Navigation%20Flow%20Chart.png)

# Project Credits
Ammar Alvi

Shannon D'Souza

# Video Link
https://www.youtube.com/watch?v=_aDb7OR65XA 


