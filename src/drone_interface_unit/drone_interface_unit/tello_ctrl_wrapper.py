from djitellopy import Tello
import djitellopy
import socket
from threading import Thread, Lock

import time

# why on earth did python allow globals?!
threads_initialized = False
drones = {}
client_socket: socket.socket

class MyTello(Tello):
    def __init__(self,
                 host=Tello.TELLO_IP,
                 retry_count=Tello.RETRY_COUNT,
                 vs_udp=Tello.VS_UDP_PORT):

        self._lock = Lock() # custom lock

        global threads_initialized, client_socket, drones

        self.address = (host, Tello.CONTROL_UDP_PORT)
        self.stream_on = False
        self.retry_count = retry_count
        self.last_received_command_timestamp = time.time()
        self.last_rc_control_timestamp = time.time()

        if not threads_initialized:
            # Run Tello command responses UDP receiver on background
            client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            client_socket.bind(("", Tello.CONTROL_UDP_PORT))
            response_receiver_thread = Thread(target=MyTello.udp_response_receiver)
            response_receiver_thread.daemon = True
            response_receiver_thread.start()

            # Run state UDP receiver on background
            state_receiver_thread = Thread(target=MyTello.udp_state_receiver)
            state_receiver_thread.daemon = True
            state_receiver_thread.start()

            threads_initialized = True
        

        drones[host] = {'responses': [], 'state': {}}

        self.LOGGER.info("Tello instance was initialized. Host: '{}'. Port: '{}'.".format(host, Tello.CONTROL_UDP_PORT))

        self.vs_udp_port = vs_udp

    @staticmethod
    def udp_response_receiver():
        while True:
            try:
                data, address = client_socket.recvfrom(1024)

                address = address[0]
                Tello.LOGGER.debug('Data received from {} at client_socket'.format(address))

                if address not in drones:
                    continue

                drones[address]['responses'].append(data)

            except Exception as e:
                Tello.LOGGER.error(e)
                break

    @staticmethod
    def udp_state_receiver():
        # TODO should not be initialized in local thread?!
        state_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        state_socket.bind(("", Tello.STATE_UDP_PORT))

        while True:
            try:
                data, address = state_socket.recvfrom(1024)

                address = address[0]
                Tello.LOGGER.debug('Data received from {} at state_socket'.format(address))

                if address not in drones:
                    continue

                data = data.decode('ASCII')
                data = Tello.parse_state(data)
                data['received_at'] = datetime.now()
                drones[address]['state'] = data

            except Exception as e:
                Tello.LOGGER.error(e)
                break