
import rclpy
import rclpy.node
from builtin_interfaces.msg import Time
from rclpy.clock import Clock

import random
import a1_interfaces.msg as a1_interfaces
import sensor_msgs.msg as sensor_msgs


#import image_source_rand as image_source

class SomeNode(rclpy.node.Node):
    def __init__(self):
        super().__init__("camera_node")
        
        self.pub_channel = self.create_publisher(sensor_msgs.Image, "ppmrob_chatter", 10)
        self.create_timer(1.0, self.timer_callback)
        self.get_logger().info("camera ACTIVE")

    def timer_callback(self):
        msg = get_image()
        self.pub_channel.publish(msg)



def main(args=None):
    rclpy.init(args=args)
    node=SomeNode()
    
    rclpy.spin(node)

    rclpy.shutdown()

if __name__ == "__main__":
    main()


def random_image(size, channels):
    return tuple(random.randint(200, 255) for i in range(size*size*channels))

def convert_to_msg(raw_data, size, channels, encoding):
    now = Clock().now().to_msg()
    image = sensor_msgs.Image()
    image.header.stamp = now
    image.height = size
    image.width = size
    image.encoding = encoding
    image.step = size * channels
    image.data = raw_data
    return image
    
def get_image():
    raw = random_image(300, 3)
    return convert_to_msg(raw, 300, 3, 'rgb8')