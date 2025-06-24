import rclpy
from rclpy.node import Node
from rclpy.callback_groups import ReentrantCallbackGroup
import threading
from .djitellopy import Tello,TelloException

from drone_system_msgs.msg import DroneNativeStatus
from drone_system_msgs.srv import DroneInterfaceCommand
from sensor_msgs.msg import Image as ImageMsg


class DroneInterfaceNode(Node):
        def __init__(self):
            super().__init__("drone_interface_node")
            self.logger = self.get_logger()

            self.telem_pub = self.create_publisher(DroneNativeStatus, '/drone/telemetry', 10)
            self.image_pub = self.create_publisher(ImageMsg, '/camera/raw', 10)

            self.tello = Tello(host="172.18.0.2", state_callback=self.publish_telemetry)
            self.tello.connect()
            #tello.streamon()  # TODO
            #frame_read = tello.get_frame_read(with_queue = True)
            self.logger.info("successfully connected to drone")

            self.cb_group = ReentrantCallbackGroup()
            self.drone_command_srv = self.create_service(
                DroneInterfaceCommand, '/drone/cmd',
                self.drone_command_srv_callback,
                callback_group=self.cb_group)

        
        def drone_command_srv_callback(self, request, response):
            try:
                match request.action:
                    case DroneInterfaceCommand.Request.DRONE_TAKEOFF:
                        self.tello.takeoff()
                    case DroneInterfaceCommand.Request.DRONE_LAND:
                        self.tello.land()
                    case DroneInterfaceCommand.Request.DRONE_EMERG:
                        self.tello.emergency()
                    case DroneInterfaceCommand.Request.DRONE_STOP:
                        self.tello.stop()
                    case DroneInterfaceCommand.Request.DRONE_MOVE:
                        self.tello.go_xyz_speed(int(request.x), int(request.y), int(request.z), 30)
                    case DroneInterfaceCommand.Request.DRONE_ROTATE:
                        self.tello.rotate_counter_clockwise(request.angle)
                response.status = DroneInterfaceCommand.Response.STATUS_SUCCESS
            except TelloException as e:
                self.logger.error("Failed to run command")
                response.status = DroneInterfaceCommand.Response.STATUS_FAIL
            return response
        
        def publish_telemetry(self):
            state = self.tello.get_current_state()
            msg = DroneNativeStatus()
            try:
                msg.agx = state['agx']
                msg.agy = state['agy']
                msg.agz = state['agz']

                msg.vgx = state['vgx']
                msg.vgy = state['vgy']
                msg.vgz = state['vgz']

                msg.pitch = state['pitch']
                msg.yaw = state['yaw']
                msg.roll = state['roll']

                msg.height = state['h']
                msg.baro = state['baro']
                msg.templ = state['templ']
                msg.temph = state['temph']
                msg.bat = state['bat']
                msg.time_motor_on = state['time']
                self.telem_pub.publish(msg)

            except KeyError as e:
                self.logger.error("exception mapping key " + str(e))

        def on_publish_image(self, frame):
            pass

def main():
    rclpy.init()
    node = DroneInterfaceNode()
    executor = rclpy.executors.MultiThreadedExecutor()
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()