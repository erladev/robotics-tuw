import rclpy
from rclpy.node import Node
from .tello_ctrl_wrapper import MyTello
from djitellopy import Tello,TelloException


from drone_system_msgs.srv import DroneInterfaceCommand

class DroneInterfaceNode(Node):
        def __init__(self):
            super().__init__("drone_interface_node")
            self.tello = Tello()

            self.logger = self.get_logger()
            self.drone_command_srv = self.create_service(DroneInterfaceCommand, '/drone/cmd',
            self.drone_command_srv_callback)
        
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
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()