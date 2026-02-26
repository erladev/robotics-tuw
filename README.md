# PPMROB WS24 - Technical Report
"A full navigation+command stack for the DJI Tello EDU with RTS-style positioning commands"

The DJI Tello EDU offers easy relative positioning commands and a camera feed. However, it has no capabilities for absolute positioning, self-localisation, or environment mapping; and its SDK control is not usable for end-users.
This project aims to solve those problems. It implements the following:
### Requirements
- VSLAM (visual self-localisation & mapping) navigation using the drones forward camera feed, yielding position data and a pointcloud map.
  One must note that most 
- a command unit, which can handle absolute repositioning commands, and preemption of a running movement goal with emergency commands.
	- the command unit is also responsible for tracking drone state, and rejects commands if preconditions are not met (e.g. movement if the drone is not airborne or falling to the ground due to emergency thrust cutoff)
- a dedicated *drone interface unit* which proxies all drone interactions, to enable modular design and deal with connection issues.
- a graphical user interface implemented with the rviz2 program, which allows:
	- showing the camera feed
	- visualizing the drone's position and the pointcloud map
	- status flags such as whether the drone is airborne or in emergency shutdown mode
	- basic commands (land, takeoff, ...)
	- turning & adjusting altitude
	- position commands in the style of an RTS (real-time strategy) game. This uses a custom tool for rviz2.

### Non-Goals
- Easy bootstrapping of the system / drone connection / map export.
- use of intertia data for self-localization.
- obstacle avoidance, pathfinding.
- corner cases around tello state, such as *takeoff* command followed by immediate *stop*.

## Off-the-shelf components
Many components can be used as-is or with minor adjustments:
- Stella-VSLAM https://github.com/stella-cv/stella_vslam is a full ros2 VSLAM implementation. (crucially, one of the view allowing non-stereo, non-inertial VSLAM)
  It is a fork of the previous ORB-SLAM method https://arxiv.org/abs/1502.00956, which has a published paper but had its software release retracted over copyright concerns https://github.com/xdspacelab/openvslam/wiki/Termination-of-the-release
- rviz2 serves as the base gui application and implements most required functionality, except RTS position-goals and a tailored status/command panel for the drone.
- ROS2 provides messaging/RPC, nodes, tf2 for reference frame transformation, opencv for dealing with camera images; also some utility nodes such as *robot_state_publisher*
- The custom rviz2 plugins are based on the respective tool tutorials and use QT5 tools https://github.com/MetroRobots/rviz_panel_tutorial, https://github.com/MetroRobots/rviz_plugin_tutorial
- DJITelloPy provides a basis for drone control, it was modified though for better event handling. https://github.com/damiafuentes/DJITelloPy


# License
Note that this project uses submodules, which may have different copyright or license. The contents of THIS repository are licensed under the GNU General Public License v3.