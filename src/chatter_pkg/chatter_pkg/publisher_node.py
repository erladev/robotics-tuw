import rclpy
import rclpy.node

class PublisherNode(rclpy.node.Node):
    def __init__(self):
        super().__init__("publisher_node")
        self.counter = 0
        self.pub_channel = self.create_publisher(TrafficChatterMessage, "ppmrob_chatter", 10)
        self.create_timer(1.0, self.timer_callback)
        self.get_logger().info("Talker ACTIVE")

    def timer_callback(self):
        self.seq_counter += 1
        msg = TrafficChatterMessage()
        msg.seq_count = self.counter
        if (self.seq_counter_%2 == 0):
            msg.message="Tick"
        else:
            msg.message="Tock"
        self.pub_channel.publish(msg)

# STANDARD MAIN BLOCK
def main(args=None):
    rclpy.init(args=args)
    node=PublisherNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()