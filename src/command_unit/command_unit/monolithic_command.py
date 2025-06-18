from enum import Enum

import rclpy

from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
import tf2_geometry_msgs

from std_msgs.msg import String as StringMsg
import geometry_msgs.msg
from drone_system_msgs.msg import DroneCommand, DroneCommandFlags
import threading, time

class Control:
    def __init__(self, node):
        self.offline=False # simulate
        self.not_airborne=True
        self.emergency_set=False

        self.tf_buffer = Buffer()

        self.node = node
        self.tf_listener = TransformListener(self.tf_buffer, node)
        #node.create_subscription()
        self.logger = node.get_logger()
        self.action_sub = node.create_subscription(
            DroneCommand,
            '/gui/actions',
            self.on_action_msg,
            2)
        self.flags_pub = node.create_publisher(DroneCommandFlags, '/cmd/flags', 10)
        self.clear_emerg_timer = None
        self.publish_flags()
    
    def publish_flags(self):
        msg = DroneCommandFlags()
        msg.not_airborne = self.not_airborne
        msg.emergency = self.emergency_set
        msg.not_connected = self.offline
        self.flags_pub.publish(msg)

    def is_exception_state(self):
        return self.offline or self.not_airborne or self.emergency_set

    # handle action, change state, return false to inhibit control commands based on action
    def on_action(self, command):
        match command.action:
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
                    self.clear_emerg_timer = self.node.create_timer(1, self.clear_emerg, callback_group=None)
                    return True
                else: return False
            case DroneCommand.ACTION_STOP:
                return not (self.offline or self.emergency_set)
            case DroneCommand.ACTION_MOVE:
                if self.is_exception_state():
                    return False
                return self.abs_move_cmd(command)


        def __str__(self):
            return str(self.__dict__)

    def on_action_msg(self, msg):
        s_ok = self.on_action(msg)
        self.publish_flags()
        self.logger.info(f"Command {msg.action} is ok: {s_ok}")

    def clear_emerg(self):
        self.logger.info("Clear emergency")
        self.emergency_set = False
        self.not_airborne = True
        self.publish_flags()
        self.clear_emerg_timer.destroy()
    
    def abs_move_cmd(self, msg):
        pose = geometry_msgs.msg.Pose()
        pose.position.x = msg.x
        pose.position.y = msg.y
        pose.position.z = msg.z
        # leave out quaternion

        to_frame = "odom"
        from_frame = "map"
        
        if self.is_exception_state():
            self.logger.info("Cannot follow move command due to exception state "+str(self))
            return False
        try:
            transform = self.tf_buffer.lookup_transform(
                to_frame,
                from_frame,
                rclpy.time.Time())
            pose_rel = tf2_geometry_msgs.do_transform_pose(pose, transform)
            self.logger.info(f"issue relative position command: {pose_rel}")
            return True
        except TransformException as ex:
            self.logger.info(
                f'Could not transform {from_frame} to {to_frame}: {ex}')
            return False
