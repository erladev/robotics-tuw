#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
import sensor_msgs.msg as sensor_msgs
class ListenerNode(Node):
    def __init__(self):
        super().__init__("ppmrob_listener")
        self.seq_count_ = 0
        self.chatter_listern_ = self.create_subscription(sensor_msgs.Image,"ppmrob_chatter",
        self.message_rx_callback, 10)
        self.get_logger().info("PPMROB Listener startet.")

    def message_rx_callback(self, msg):
        print(f"msg received. time {msg.header.stamp}")
        
def main(args=None):
    # initialize ROS2 (com)
    rclpy.init(args=args)
    node=ListenerNode()
    rclpy.spin(node)
    # shutdown ROS2
    rclpy.shutdown()

if __name__ == "__main__":
    main()