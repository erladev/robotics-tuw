import socket
import threading
import time

def send_periodic_messages(address, stop_event):
    # Use a different port for periodic messages
    target_port = 8890
    target_address = (address[0], target_port)
    message = b"pitch:0;roll:0;yaw:0;vgx:0;vgy:0;vgz:0;templ:0;temph:0;tof:0;h:0;bat:0;baro:0.00;time:0;agx:0.00;agy:0.00;agz:0.00;\r\n"

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        while not stop_event.is_set():
            sock.sendto(message, target_address)
            #print(f"Sent periodic update to {target_address}")
            time.sleep(2)
    finally:
        sock.close()

def run_udp_server():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ('0.0.0.0', 8889)
    print(f"Starting UDP server on {server_address}")
    sock.bind(server_address)

    threads = {}
    stop_events = {}

    try:
        while True:
            data, address = sock.recvfrom(4096)
            command = data.decode().strip()
            print(f"Received from {address}: {command}")

            # Respond with "ok"
            sock.sendto(b"ok", address)

            # Start a new thread if the command is "command"
            if command == "command":
                if address not in stop_events:
                    stop_events[address] = threading.Event()
                    thread = threading.Thread(
                        target=send_periodic_messages,
                        args=(address, stop_events[address])
                    )
                    thread.daemon = True
                    thread.start()
                    threads[address] = thread
                    print(f"Started periodic updates for {address}")
                else:
                    print(f"Already sending periodic updates to {address}")
    finally:
        for event in stop_events.values():
            event.set()
        for thread in threads.values():
            thread.join(timeout=1)
        sock.close()

if __name__ == "__main__":
    run_udp_server()
