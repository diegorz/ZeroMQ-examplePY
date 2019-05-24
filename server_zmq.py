# -*- coding: utf-8 -*-
"""

Alba Portal project - TID Chile, 2019.

"""
from communication import Communication
import time


class Server:
    """
    Server that sends or receives messages as the case may be
    """

    def __init__(self):
        server_socket = Communication.create_server(Communication.zmq_type_socket('PULL'),
                                                    "ipc:///tmp/tunnel-zmq")

        while True:
            # In this case, server take messages sent by client because the pattern of messaging is PUSH/PULL
            obj = server_socket.recv_pyobj()
            print("Receiving object...")
            print(obj)
            time.sleep(1)


if __name__ == "__main__":
    run_server = Server()
