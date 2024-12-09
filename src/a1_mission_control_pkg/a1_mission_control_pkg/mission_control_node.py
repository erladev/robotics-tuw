import rclpy
import time
import sys
from threading import Thread
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from std_msgs.msg import String
import PyQt5
from PyQt5.QtWidgets import QApplication, QLabel, QMainWindow, QWidget, QPushButton, QMainWindow

class MyGuiNode(Node):
    def __init__(self):
        super().__init__("simple_gui_node")



def main(args=None):
    rclpy.init(args=args)
    
    app = QApplication(sys.argv)
    HMI = QMainWindow()
    #ui  = Ui_MainWindow()
    #ui.setupUi(HMI)

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