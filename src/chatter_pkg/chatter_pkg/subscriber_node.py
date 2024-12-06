import rclpy
import rclpy.node

from chatter_interfaces.msg import TrafficChatterMessage

class SubscriberNode(rclpy.node.Node):
    def __init__(self):
        super().__init__("subscriber_node")
        self.recv_count = 0
        self.sub_channel = self.create_subscription(TrafficChatterMessage, "ppmrob_chatter",
        self.message_recv_callback, 10)
        self.get_logger().info("Listener node ACTIVE")

    def message_recv_callback(self, msg):
        self.recv_count += 1
        if self.recv_count > msg.seq_count:
            self.recv_count = msg.seq_count
            self.get_logger().info("Reset recv seq counter")
        self.get_logger().info(f"received msg (seq={msg.seq_count} data {msg.message}")

# STANDARD MAIN BLOCK
def main(args=None):
    rclpy.init(args=args)
    node=SubscriberNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()