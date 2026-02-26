from launch import LaunchDescription
from launch_ros.actions import Node
import sys
import os

# Ensure paths.py can be imported (add parent dir to sys.path)
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
import paths

def generate_launch_description():
    return LaunchDescription([
        # SLAM system (stella_vslam_ros)
        Node(
            package='stella_vslam_ros',
            executable='run_slam',
            name='slam_node',
            output='screen',
            arguments=[
                '--viewer', 'none',
                '--vocab', paths.ORB_VOCAB,
                '--config', paths.CONFIG_YAML
            ]
        ),

        # Static transform: odom -> base_link
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='static_tf_pub',
            arguments=['0', '0', '0', '0', '0', '0', 'odom', 'base_link'],
            output='screen'
        ),

        # Robot state publisher
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            arguments=[paths.URDF_FILE],
            output='screen'
        ),

        # RViz2 with predefined config
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', paths.RVIZ_CONFIG],
            output='screen'
        ),

        # Drone interface unit
        Node(
            package='drone_interface_unit',
            executable='drone_interface_node',
            name='drone_interface_node',
            output='screen'
        ),

        # Command unit
        Node(
            package='command_unit',
            executable='command_node',
            name='command_node',
            output='screen'
        ),
    ])
