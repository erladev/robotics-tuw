import rclpy
from rclpy.node import Node
import queue
import threading, time
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
from drone_system_msgs.msg import DroneCommand
import command_unit.monolithic_command as monolithic_command
from drone_system_msgs.msg import DroneCommand, DroneCommandFlags
from drone_system_msgs.srv import DroneInterfaceCommand


class CommandNode(Node):
    def __init__(self):
        super().__init__("command_node")
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        
        self.action_sub = self.create_subscription(
            DroneCommand,
            '/gui/actions',
            self.on_action_msg,
            2)
        self.flags_pub = self.create_publisher(DroneCommandFlags, '/cmd/flags', 10)
        self.drone_if = self.create_client(DroneInterfaceCommand, '/drone/cmd')
        self.logger = self.get_logger()
        self.queue = queue.Queue()
        self.flag_preemption = False
        self.flag_worker_shutdown = False
        self.command = monolithic_command.MonolithicControl(self)

        threading.Thread(target=self.command_worker).start()
    

    # TODO delegate to worker thread
    def on_action_msg(self, msg):
        if self.command.is_preemptive(msg):
            clear_queue(self.queue)
            self.flag_preemption = True
        self.queue.put(msg)

    # return True=success, False=fail, None=preempt
    def call_drone_if(self, command):
        future = self.drone_if.call_async(command)
        while True:
            if future.done():
                response = future.result()
                return response.status == DroneInterfaceCommand.Response.STATUS_SUCCESS
            elif self.flag_preemption:
                self.logger.info("drone interface call preempted.")
                return None
            time.sleep(0.05)

    def command_worker(self):
        self.logger.info("command worker loop started.")
        while True:
            command = self.queue.get()
            self.flag_preemption = False
            # shutdown
            if self.flag_worker_shutdown:
                self.logger.info("command worker loop terminating.")
                break
            self.logger.info("worker loop processing command.")
            self.command.on_action_msg(command)

def clear_queue(q):
    try:
        while True:
            q.get_nowait()
    except queue.Empty:
        pass

def main():
    rclpy.init()
    node = CommandNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt: pass
    finally:
        node.flag_worker_shutdown = True
        node.flag_preemption = True
        node.queue.put(None)
        node.destroy_node()

if __name__ == '__main__':
    main()