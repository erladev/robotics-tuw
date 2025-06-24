from enum import Enum

import rclpy

from tf2_ros import TransformException
import tf2_geometry_msgs

from std_msgs.msg import String as StringMsg
import geometry_msgs.msg
from drone_system_msgs.msg import DroneCommand, DroneCommandFlags
from drone_system_msgs.srv import DroneInterfaceCommand
import threading, time

class MonolithicControl:
    def __init__(self, node):
        self.node = node

        self.offline=False # simulate
        self.not_airborne=False # simulate takeoff TODO
        self.emergency_set=False

        self.logger = node.get_logger()
        self.publish_flags()
    
    def publish_flags(self):
        msg = DroneCommandFlags()
        msg.not_airborne = self.not_airborne
        msg.emergency = self.emergency_set
        msg.not_connected = self.offline
        self.node.flags_pub.publish(msg)

    def is_exception_state(self):
        return self.offline or self.not_airborne or self.emergency_set

    # handle action, change state, return false to inhibit control commands based on action
    def on_action(self, command):
        match command.action:
            case DroneCommand.ACTION_TAKEOFF:
                if not (self.offline or self.emergency_set):
                    req = DroneInterfaceCommand.Request()
                    req.action = DroneInterfaceCommand.Request.DRONE_TAKEOFF
                    r = self.node.call_drone_if(req)
                    if r is not False: # t/o likely succeeds even if interrupted
                        self.not_airborne = False
                    return r
                return False
            case DroneCommand.ACTION_LAND:
                if not (self.offline or self.not_airborne or self.emergency_set):
                    req = DroneInterfaceCommand.Request()
                    req.action = DroneInterfaceCommand.Request.DRONE_LAND
                    r = self.node.call_drone_if(req)
                    if r:           # land likely wont succeed if preempted
                        self.not_airborne = True
                        return r
                return False
            case DroneCommand.ACTION_EMERG:
                if not self.offline:
                    req = DroneInterfaceCommand.Request()
                    req.action = DroneInterfaceCommand.Request.DRONE_EMERG
                    r = self.node.call_drone_if(req)
                    if not r: self.logger.warning("emergency call failed: " + str(r))
                    self.emergency_set = True
                    clear_emerg_timer = []
                    clear_emerg_timer.append(self.node.create_timer(1, lambda: self.clear_emerg(clear_emerg_timer), callback_group=None))
                    return True
                else: return False
            case DroneCommand.ACTION_STOP:
                if not (self.offline or self.emergency_set):
                    req = DroneInterfaceCommand.Request()
                    req.action = DroneInterfaceCommand.Request.DRONE_STOP
                    return self.node.call_drone_if(req)
                else:
                    return False
            case DroneCommand.ACTION_MOVE:
                if self.is_exception_state():
                    return False
                return self.abs_move_cmd(command) # return handled in method
            case DroneCommand.ACTION_ALTITUDE:
                if self.is_exception_state():
                    return False
                return self.abs_move_cmd(command, only_altitude=True)
            case DroneCommand.ACTION_ROTATE_REL:
                if self.is_exception_state():
                    return False
                req = DroneInterfaceCommand.Request()
                req.action = DroneInterfaceCommand.Request.DRONE_ROTATE
                req.angle = command.angle
                return self.node.call_drone_if(req)

        def __str__(self):
            return str(self.__dict__)

    def is_preemptive(self, msg):
        return msg.action in (DroneCommand.ACTION_STOP, DroneCommand.ACTION_EMERG)

    def on_action_msg(self, msg):
        s_ok = self.on_action(msg)
        self.publish_flags()
        self.logger.info(f"Command {msg.action} is ok: {s_ok}")

    def clear_emerg(self, own_timer):
        self.logger.info("Clear emergency")
        self.emergency_set = False
        self.not_airborne = True
        self.publish_flags()
        own_timer[0].destroy()
    
    def abs_move_cmd(self, msg, only_altitude=False):
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
            transform = self.node.tf_buffer.lookup_transform(
                to_frame,
                from_frame,
                rclpy.time.Time())
            pose_rel = tf2_geometry_msgs.do_transform_pose(pose, transform)
            self.logger.info(f"issue relative move command: {pose_rel}")
            req = DroneInterfaceCommand.Request()
            req.action = DroneInterfaceCommand.Request.DRONE_MOVE
            if not only_altitude:
                req.x = pose_rel.position.x * 100
                req.y = pose_rel.position.y * 100
            req.z = pose_rel.position.z * 100
            if abs(req.x) < 20 and abs(req.y) < 20 and abs(req.z) < 20:
                self.logger.info(f"cannot move, distance too small: {pose_rel}")
                return False
            return self.node.call_drone_if(req)

        except TransformException as ex:
            self.logger.info(
                f'Could not transform {from_frame} to {to_frame}: {ex}')
            return False
