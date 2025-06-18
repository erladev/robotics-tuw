import rclpy
from rclpy.node import Node

from drone_system_msgs.msg import DroneCommand
import command_unit.monolithic_command as monolithic_command

class CommandNode(Node):
        def __init__(self):
            super().__init__("command_node")
            self.command = monolithic_command.Control(self)


def main():
    rclpy.init()
    node = CommandNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()