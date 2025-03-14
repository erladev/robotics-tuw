import rclpy
from rclpy.node import Node

from drone_system_msgs.srv import DroneCommand

class DroneInterfaceNode(Node):
        def __init__(self):
            super().__init__("drone_interface_node")
            self.drone_command_srv = self.create_service(DroneCommand, 'drone_cmd',
            self.drone_command_srv_callback)
        
        def drone_command_srv_callback(self, request, response):
            response.status = DroneCommand.STATUS_SUCCESS
            return response


def main():
    rclpy.init()
    node = DroneInterfaceNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()