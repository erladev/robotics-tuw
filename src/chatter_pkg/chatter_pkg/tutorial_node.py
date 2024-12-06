#!/usr/bin/env python3

import rclpy
import rclpy.node

class SomeNode(rclpy.node.Node):
    def __init__(self):
        super().__init__("py_node_basic")
        self.get_logger().info("Node ACTIVE")

def main(args=None):
    rclpy.init(args=args)
    node=SomeNode()
    
    rclpy.spin(node)

    rclpy.shutdown()

if __name__ == "__main__":
    main()