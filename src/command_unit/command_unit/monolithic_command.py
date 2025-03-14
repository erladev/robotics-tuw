from enum import Enum

import rclpy

from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
import tf2_geometry_msgs

from std_msgs.msg import String as StringMsg
import geometry_msgs.msg
from drone_system_msgs.msg import DroneCommand


class Control:
    def __init__(self, node):
        self.offline=False # simulate
        self.not_airborne=True
        self.emergency_set=False

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, node)
        #node.create_subscription()
        self.logger = node.get_logger()
        self.action_sub = node.create_subscription(
            StringMsg,
            '/drone_gui/action',
            self.on_action_msg,
            2)
        self.goal_pose_sub = node.create_subscription(
            geometry_msgs.msg.PoseStamped,
            '/goal_pose',
            self.on_goal_pose,
            2
        )
    
    def is_exception_state(self):
        return self.offline or self.not_airborne or self.emergency_set

    # handle action, change state, return false to inhibit control commands based on action
    def on_action(self, action):
        match action:
            case DroneCommand.ACTION_TAKEOFF:
                if not (self.offline or self.emergency_set):
                    self.not_airborne = False
                    return True
                else: return False
            case DroneCommand.ACTION_LAND:
                if not (self.offline or self.not_airborne or self.emergency_set):
                    self.not_airborne = True
                    return True
                else: return False
            case DroneCommand.ACTION_EMERG:
                if not self.offline:
                    self.emergency_set = True
                    return True
                else: return False
            case DroneCommand.ACTION_STOP:
                return not (self.offline or self.emergency_set)
            case "reset_emerg":
                if not self.offline:
                    self.emergency_set = False
                    return True
                else: return False

        def __str__(self):
            return str(self.__dict__)

    def on_action_msg(self, msg):
        # move_rel/rotate_rel are not directly implemented, goalPose instead
        s_ok = self.on_action(msg.data)
        self.logger.info(f"Command {msg.data} is ok: {s_ok}")
    
    def on_goal_pose(self, msg):
        if self.is_exception_state():
            self.logger.info("Cannot follow move command due to exception state "+str(self))
            return
        try:
            transform = self.tf_buffer.lookup_transform(
                "odom", # to frame
                "map",  # from frame
                rclpy.time.Time())
            pose_rel = tf2_geometry_msgs.do_transform_pose(msg.pose, transform)
            self.logger.info(f"issue relative position command: {pose_rel}")
        except TransformException as ex:
            self.get_logger().info(
                f'Could not transform {to_frame_rel} to {from_frame_rel}: {ex}')
            return
