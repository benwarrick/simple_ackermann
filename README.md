# simple_ackermann
An especially simple and efficient URDF ackermann steering vehicle. This model will serve as the base for more complex simulations, such as the Polaris Gem e2, and will function as an accessible Ackermann model for LTU students' learning and research activities.  

Requires Gazebo simulator to be installed: http://gazebosim.org/tutorials?tut=install_ubuntu&cat=install
Also, you may have to experiment with video drivers. I've had good luck with Ubuntu's standard graphics driver (nouveau) on GM108M [GeForce 840M] (rev a2) for one system, and on another nvidia-384 seems to be working well on GP104 [GeForce GTX 1070]. 

## Clone the repository into the src folder (or sub folder) of your catkin workspace.

```git clone https://github.com/benwarrick/simple_ackermann.git```

## Clone the velodyne_simulator into the same src. 

```git clone https://github.com/florianshkurti/velodyne_simulator.git```

## Install needed ackerman packages
```
sudo apt-get install ros-kinetic-ackermann-msgs
sudo apt-get install ros-kinetic-ackermann-steering-controller
```

## Make sure controller packages are installed

```
sudo apt-get install ros-kinetic-joint-state-controller  
sudo apt-get install ros-kinetic-effort-controllers  
sudo apt-get install ros-kinetic-position-controllers
```

In the main catkin directory, run catkin_make.

You may also need to install libignition-math2-dev to get a file used by the Velodyne plugins, Inertial.hh. If you get the following error:

[workspace]/src/GazeboSimulatorModel/velodyne_gazebo_plugins/src/GazeboRosVelodyneLaser.cpp:35:
/usr/include/gazebo-7/gazebo/msgs/msgs.hh:24:37: fatal error: ignition/math/Inertial.hh: No such file or directory

## Run the following to install the library: 

```
sudo apt-get install libignition-math2-dev
```
## Add the driving course ground plain
Inside the "items" folder is a zip file, course_ground_plane.zip. Unzip and move the folder called course_ground_plan. Move this folder into your gazebo modules folder: ~/.gazebo/modules  

Note: .gazebo is a hidden folder in your home directory. You can unhide hidden folder with Ctrl+h in the file browser. 


## Setup the terminal.

```
source devel/setup.sh
```

## Run either the ackermann vehicle with only the camera, or with LiDAR as well. 

```
roslaunch ackermann_vehicle_gazebo ackermann_vehicle.launch
roslaunch ackermann_vehicle_gazebo ackermann_vehicle_lidar.launch
