# Vacuum Gripper for Value-Up 2024
<img src= "https://github.com/user-attachments/assets/05ab714e-d31a-4fed-9c38-53d1a6a998bf" width="300" height="380" /> 


## Notes

· This is a package for vacuum gripper using Arduino-based vacuum pumps and electronic valves.

· It uses _rosserial_ package to make UART-based communication between the computer and Arduino Uno.

· The _vacuum_gripper_code_for_arduino_upload.ino_ is already uploaded to the Arduino UNO. Generally, you don't need to worry about this step.


## Preparation

### 1. Install Arduino IDE 1.8.19 (Legacy Version)

#### 1.1. Download Arduino IDE 1.8.19
[Download from the official Arduino website](https://www.arduino.cc/en/software).

#### 1.2. Extract the Package
Extract the downloaded package.

#### 1.3. Install the IDE
Open a terminal and navigate to the extracted package directory, then run the following commands:
```sh
cd ~/<YOUR_DIRECTORY>/arduino-1.8.19/
sudo sh install.sh
```

#### 1.4. Set Serial Port Permission
Ensure the correct permissions for the serial port:
```sh
ls -l /dev/tty*
sudo usermod -a -G dialout <username>
```
### 2. Install and Configure ROS Serial

#### 2.1. Install rosserial
Install the required ROS packages:
```sh
sudo apt-get install ros-noetic-rosserial ros-noetic-rosserial-server ros-noetic-rosserial-arduino
```
#### 2.2. Generate ros_lib
Generate the ROS libraries for Arduino:
```sh
cd ~/<YOUR_DIRECTORY>/arduino-1.8.19/libraries/
rm -rf ros_lib
rosrun rosserial_arduino make_libraries.py .
```
## How to Use
### 1. Start ROS Core
Open a terminal and start the ROS core:
```sh
roscore
```

### 2. Run the ROS Serial Node
In a second terminal, run the ROS serial node:
```sh
rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB1 _baud:=57600
```
* name of port could be different. (ex. ttyUSB0, ttyUSB1, ttyACM0,ttyACM1...)

### 3. Run the Vacuum Gripper Control
In a third terminal, run the vacuum gripper control script:
```sh
rosrun vacuum_gripper vacuum_gripper_control.py
```

