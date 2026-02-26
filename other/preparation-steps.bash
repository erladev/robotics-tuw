# basic setup steps
# assumes you are in workdir

echo "setting up global and project ROS components"
. /opt/ros/humble/setup.bash
. install/setup.bash

echo "configuring linker dir"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

echo "rebuilding"
colcon build --packages-skip rviz odom_to_tf_ros2 sioclient socket_publisher