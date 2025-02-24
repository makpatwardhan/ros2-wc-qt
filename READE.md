

Installing ros2 rolling desktop 

sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu noble main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
sudo apt update
sudo apt install ros-rolling-desktop
sudo apt install ros-rolling-service-msgs

verify ROS rolling installtion 

source /opt/ros/rolling/setup.bash

run simple publish and subcribe example 

open one terminal and run the below command 
ros2 run demo_nodes_cpp talker (publisher)
open another terminal and run the below command 
ros2 run demo_nodes_cpp listener (subscriber)
 
 check rviz using below command 
 rviz2


-- Creating the ROS package 
ros2 pkg create --build-type ament_cmake --node-name subscriber my_package_cpp
colcon build
source install/setup.bash
ros2 run my_package_cpp subscriber

