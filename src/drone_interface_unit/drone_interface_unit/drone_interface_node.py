import rclpy
from rclpy.node import Node
from rclpy.callback_groups import ReentrantCallbackGroup
from .djitellopy import Tello,TelloException

from drone_system_msgs.srv import DroneInterfaceCommand

class DroneInterfaceNode(Node):
        def __init__(self):
            super().__init__("drone_interface_node")
            self.tello = Tello(host="172.18.0.2")
            self.tello.connect()

            self.logger = self.get_logger()
            self.cb_group = ReentrantCallbackGroup()
            self.drone_command_srv = self.create_service(
                DroneInterfaceCommand, '/drone/cmd',
                self.drone_command_srv_callback,
                callback_group=self.cb_group)
        
        def drone_command_srv_callback(self, request, response):
            try:
                match request.action:
                    case DroneInterfaceCommand.Request.DRONE_TAKEOFF:
                        self.tello.takeoff()
                    case DroneInterfaceCommand.Request.DRONE_LAND:
                        self.tello.land()
                    case DroneInterfaceCommand.Request.DRONE_EMERG:
                        self.tello.emergency()
                    case DroneInterfaceCommand.Request.DRONE_STOP:
                        self.tello.stop()
                    case DroneInterfaceCommand.Request.DRONE_MOVE:
                        self.tello.go_xyz_speed(int(request.x), int(request.y), int(request.z), 30)
                    case DroneInterfaceCommand.Request.DRONE_ROTATE:
                        self.tello.rotate_counter_clockwise(request.angle)
                response.status = DroneInterfaceCommand.Response.STATUS_SUCCESS
            except TelloException as e:
                self.logger.error("Failed to run command")
                response.status = DroneInterfaceCommand.Response.STATUS_FAIL
            return response

def main():
    rclpy.init()
    node = DroneInterfaceNode()
    executor = rclpy.executors.MultiThreadedExecutor()
    executor.add_node(node)
    executor.spin()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()