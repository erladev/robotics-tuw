import rclpy
import time
import sys
from threading import Thread
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from std_msgs.msg import String
from PyQt5.QtWidgets import QApplication, QLabel, QMainWindow, QWidget, QPushButton

class GuiNode(Node):
    def __init__(self):
        super().__init__("simple_gui_node")
        self.counter_    = 0
        self.button1_publisher_  = self.create_publisher(String, '/app/button_1', 10)
        self.button2_publisher_  = self.create_publisher(String, '/app/button_2', 10)

    def button_1_publisher_callback_(self):
        self.counter_ = self.counter_ + 1
        msg = String()
        msg.data = "Button 1 pressed"
        self.button1_publisher_.publish(msg)

    def button_2_publisher_callback_(self):
        self.counter_ = self.counter_ + 1
        msg = String()
        msg.data = "Button 2 pressed"
        self.button2_publisher_.publish(msg)

    def subscriber_callback_(self, msg):
        self.get_logger().info("Button clicked, " + msg.data)


def main(args=None):
    rclpy.init(args=args)
    
    app = QtWidgets.QApplication(sys.argv)
    HMI = QtWidgets.QMainWindow()
    ui  = Ui_MainWindow()
    ui.setupUi(HMI)

    hmi_node = MyGuiNode(ui)
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