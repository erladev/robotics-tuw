import rclpy
import time
import sys
from threading import Thread
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from std_msgs.msg import String
import PyQt5
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QLabel, QMainWindow, QWidget, QPushButton, QMainWindow, QVBoxLayout
from PyQt5.QtGui import QPixmap, QImage
import sensor_msgs.msg as sensor_msgs
from cv_bridge import CvBridge
import cv2
from datetime import datetime

class MyGuiNode(Node):
    def __init__(self):
        super().__init__("simple_gui_node")
        self.pix = QPixmap()
        self.seq_count = 0
        self.chatter_listern_ = self.create_subscription(sensor_msgs.Image,"ppmrob_chatter",
        self.message_rx_callback, 10)
        self.get_logger().info("PPMROB Listener startet.")
        self.bridge = CvBridge()
        self.image = None
        

    def message_rx_callback(self, msg):
        self.seq_count += 1
        print("received "+str(self.seq_count))
        try:
            # Convert ROS Image message to OpenCV format
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='rgb8')
            self.image = cv_image
            self.add_text(msg)
        except Exception as e:
            self.get_logger().error(f"Failed to convert image: {e}")

    def add_text(self, msg):
        sec = msg.header.stamp.sec
        nanosec = msg.header.stamp.nanosec
        timestamp = datetime.fromtimestamp(sec + nanosec / 1e9).strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]

        # Overlay timestamp on the image
        font = cv2.FONT_HERSHEY_SIMPLEX
        font_scale = 0.4
        color = (0, 0, 0)  # White text
        thickness = 1
        text_size = cv2.getTextSize(timestamp, font, font_scale, thickness)[0]
        text_x = self.image.shape[1] - text_size[0] - 10  # 10 px from right edge
        text_y = 30  # 30 px from top edge
        cv2.putText(self.image, timestamp, (text_x, text_y), font, font_scale, color, thickness, cv2.LINE_AA)


class MainWindow(QWidget):
    def __init__(self, node):
        super().__init__()
        self.node = node
        self.label = QLabel("Waiting for image...")
        self.label.setAlignment(Qt.AlignCenter)
        layout = QVBoxLayout()
        layout.addWidget(self.label)
        self.setLayout(layout)
        self.setWindowTitle("ROS2 PyQt Image Viewer")
        self.setGeometry(100, 100, 800, 600)
        self.timer_id = self.startTimer(30)  # Refresh at ~30fps

    def timerEvent(self, event):
        if self.node.image is not None:
            # Convert the OpenCV image to QImage
            height, width, channel = self.node.image.shape
            bytes_per_line = 3 * width
            qt_image = QImage(self.node.image.data, width, height, bytes_per_line, QImage.Format_RGB888)
            pixmap = QPixmap.fromImage(qt_image)
            self.label.setPixmap(pixmap)

def main(args=None):
    rclpy.init(args=args)
    
    app = QApplication(sys.argv)
    hmi_node = MyGuiNode()
    HMI = MainWindow(hmi_node)

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