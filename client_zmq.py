# -*- coding: utf-8 -*-
"""

Alba Portal project - TID Chile, 2019.

"""
from communication import Communication
import time


class Client:
    """
    Client that sends or receives messages as the case may be
    """

    def __init__(self):
        client_socket = Communication.create_client(Communication.zmq_type_socket('PUSH'),
                                                    "ipc:///tmp/tunnel-zmq")

        while True:
            # In this case, client send messages to server because the pattern of messaging is PUSH/PULL
            client_socket.send_pyobj({"rut": "99999999-9",
                                      "celular": "+56 9 99999999",
                                      "client-mac": "a9:b9:c9:d9:e9:f9",
                                      "client-ip": "0.0.0.0",
                                      })
            print("Sending Object...")
            time.sleep(1)


if __name__ == "__main__":
    run_client = Client()
