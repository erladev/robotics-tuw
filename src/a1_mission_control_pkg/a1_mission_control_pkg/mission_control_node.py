import rclpy
import time
import sys
from threading import Thread
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from std_msgs.msg import String
import PyQt5
from PyQt5.QtWidgets import QApplication, QLabel, QMainWindow, QWidget, QPushButton, QMainWindow
from PyQt5.QtGui import QPixmap
import sensor_msgs.msg as sensor_msgs


class MyGuiNode(Node):
    def __init__(self):
        super().__init__("simple_gui_node")
        self.pix = QPixmap()
        self.seq_count = 0
        self.chatter_listern_ = self.create_subscription(sensor_msgs.Image,"ppmrob_chatter",
        self.message_rx_callback, 10)
        self.get_logger().info("PPMROB Listener startet.")
        

    def message_rx_callback(self, msg):
        self.seq_count += 1
        print("received "+str(self.seq_count))

def main(args=None):
    rclpy.init(args=args)
    
    app = QApplication(sys.argv)
    HMI = QMainWindow()

    hmi_node = MyGuiNode()
    executor = MultiThreadedExecutor()
    executor.add_node(hmi_node)

    # Start the ROS2 node on a separate thread
    thread = Thread(target=executor.spin)
    thread.start()
    hmi_node.get_logger().info("Spinned ROS2 Node . . .")

    # Let the app running on the main thread
    try:
        HMI.show()
        sys.exit(app.exec_())

    finally:
        hmi_node.get_logger().info("Shutting down ROS2 Node . . .")
        hmi_node.destroy_node()
        executor.shutdown()

if __name__ == '__main__':
    main()