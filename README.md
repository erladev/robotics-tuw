# PPMROB WS24 - Technical Report
"A full navigation+command stack for the DJI Tello EDU with RTS-style positioning commands"

The DJI Tello EDU offers easy relative positioning commands and a camera feed. However, it has no capabilities for absolute positioning, self-localisation, or environment mapping; and its SDK control is not usable for end-users.
This project aims to solve those problems. It implements the following:
### Requirements
- VSLAM (visual self-localisation & mapping) using the drones forward camera feed, yielding position data in the context of a pointcloud map.
- a command unit, which can handle absolute repositioning commands, and preemption of a running movement goal with emergency commands.
	- the command unit is also responsible for tracking drone state, and rejects commands if preconditions are not met (e.g. movement if the drone is not airborne)
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
- rviz2 serves as the base gui application and implements most required functionality, except RTS position-goals and a tailored status/command panel for the drone.
- ROS2 provides messaging/RPC, nodes, tf2 for reference frame transformation, opencv for dealing with camera images; also some utility nodes such as *robot_state_publisher*
- The custom rviz2 plugins are based on the respective tool tutorials and use QT5 tools https://github.com/MetroRobots/rviz_panel_tutorial, https://github.com/MetroRobots/rviz_plugin_tutorial
- DJITelloPy provides a basis for drone control, it was modified though for better event handling. https://github.com/damiafuentes/DJITelloPy

## System Overview
Below is a diagram of the system components and how the reference frames relate.
each yellow node corresponds to a ROS2 node, edges inform data flow.
The drone communicates via UDP/IP, and only with the Drone Interface Node.
The robot state publisher and transform publisher nodes configure the reference frames as well as the custom 3d robot model displayed by rviz2.
![[architecture screenshot.png]]
## Details for nodes & code
Here the custom components shall be described; details for starting the others is found in section *Running the System*. The repository's src/ folder contains code for all colcon packages; the docker container provides a suitable build & runtime environment.

#### Drone system msgs & resources packages
Custom ros2 interfaces reside in the messages package; resources contains a custom 3d drone model (very roughly based on a bullet-physics model https://github.com/bulletphysics/bullet3/blob/master/data/Quadrotor/quadrotor_base.obj) and URDF robot description.
Interfaces include 
- DroneCommand - messages from GUI node to command node
- DroneCommandFlags - status flags emitted by command node
- DroneNativeStatus - corresponds to the dji tello status stream, sent by drone interface node
- DroneInterfaceCommand - ros2 *service*, command node calls drone interface node.

#### Drone Interface Node
The node uses modified DJITelloPy: callbacks were added to the state and image receiver threads, which directly publish to ros2 topics. Further, the node uses a reentrant call group and threadpool executor, to allow concurrent service calls. In case of an preempting service call (stop / emergency), the previous call continues normally but the stop command is nonetheless sent to the drone.

#### Command Node
The command node uses a guarded events finite state machine approach. In particular, movement commands are rejected if the drone is in an emergency state, not connected, or not airborne. It also publishes those states on a topic.
The drone interface service is called in a dedicated thread, which can be preempted in case of a stop/emergency command. State updates reasonably deal with preempted goals.
The command node also listens to the tf2 reference frame topics to translate absolute position goals into commands relative to the drone position.

#### GUI
The rviz2 ui uses the following tools: image panel, pointcloud, robot model, custom drone panel (see src/rviz_panel_tutorial), custom rts pose tool (see src/rviz_enhanced_gui_plugins), with straightforward setup.
The drone status panel subscribes to the statusflags topic and displays warnings accordingly; it also issues commands when the respective buttons are pressed.
The rts pose tool additionally listens to the tf2 buffer to draw lines from the drone position to the clicked point; it projects on a 2d plane at the drones height, and issues absolute repositioning commands.

## Camera calibration and Stella-VSLAM config
VSLAM systems must be configured with the type of camera to deal with the lens distortion. Opencv documents such a distortion model https://docs.opencv.org/2.4/doc/tutorials/calib3d/camera_calibration/camera_calibration.html, and there is a guide that helped with implementation, https://aliyasineser.medium.com/opencv-camera-calibration-e9a48bdd1844.
The scripts reside in other/opencv-calibrate: calibrate.py performs calibration based on the tutorial, to_stella_config.py converts the former scripts output to a suitable stella_vslam config file.
Distortion correction is measured by 2 matrices:
K: 3x3 matrix, which corresponds to following formula from opencv:
$$
\begin{bmatrix}
x\\ y \\ w
\end{bmatrix}
=
\begin{bmatrix}
f_x & 0 & c_x\\
0 & f_y & c_y\\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
X\\ Y \\ Z
\end{bmatrix}
$$
D: 1x5 matrix
corresponds to the distortion coefficients from opencv:
$$D = (k_1, k_2, p_1, p_2, k_3)$$

## Build Process
Colcon command:
`colcon build --packages-skip odom_to_tf_ros2 sioclient socket_publisher`

## Running the System
(assuming all packages are built; you may need to follow the stella_vslam guide https://stella-cv.readthedocs.io/en/latest/ros2_package.html#installation, colcon build should suffice though)
1. First, connect to the drone wifi
2. start docker container `docker compose up -d`
3. the nodes have to be started one by one, so you will now need multiple terminal windows, in workspace folder with activated ros2 environment.
4. `ros2 run stella_vslam_ros run_slam --viewer none --vocab /orb_vocab.fbow --config /path/to/config.yaml`
5. start static robot info:
	1. `ros2 run tf2_ros static_transform_publisher 0 0 0 0 0 0 odom base_link`
	2. `ros2 run robot_state_publisher robot_state_publisher src/resources/urdf/quad.urdf`
6. start rviz2, add panels, visualizations & tools:
	1. rts pose tool
	2. pointcloud visualization
	3. robot visualization
	4. image panel
	5. "demo panel" which is the drone status panel
7. configure rviz2 tools, some need a source topic
8. `ros2 run drone_interface_unit drone_interface_node`
   check logs to see if the connection was established succesfully
9. `ros2 run command_unit command_node`

## Evaluation