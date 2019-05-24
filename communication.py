# -*- coding: utf-8 -*-
"""

Alba project - TID Chile, 2018.

"""
import zmq.green as zmq


class Communication(object):

    @staticmethod
    def zmq_type_socket(type):
        if type == "REQ":
            return zmq.REQ
        elif type == "REP":
            return zmq.REP
        elif type == "PULL":
            return zmq.PULL
        elif type == "PUSH":
            return zmq.PUSH
        elif type == "PUB":
            return zmq.PUB
        elif type == "SUB":
            return zmq.SUB
        return None
    """
    Class by communication inter-process in Alba.
    """
    @staticmethod
    def create_server(socket_type, bind_address):
        """
        Create server socket.
        :param socket_type: ZeroMQ socket type, for example: Pull, push, Req, Rep, etc.
        :param bind_address: Protocol to use, ipc, tcp, etc.
        :return: Socket object created
        """
        try:
            context = zmq.Context()
            socket = context.socket(socket_type)
            socket.bind(bind_address)
            return socket

        except Exception as e:
            print("Exception-create_server ({0})".format(e))
            return None

    @staticmethod
    def create_client(socket_type, endpoint):
        """
        Create client socket.
        :param socket_type:  ZeroMQ socket type, for example: Pull, push, Req, Rep, etc.
        :param endpoint: Address to connect
        :return: Socket object created
        """
        try:
            context = zmq.Context()
            socket = context.socket(socket_type)
            socket.connect(endpoint)

            # SUB zeromq socket type, always must subscribe to topic.
            if socket_type == zmq.SUB:
                socket.setsockopt_string(zmq.SUBSCRIBE, '')

            return socket

        except Exception as e:
            print("Exception-create_client ({0})".format(e.args))
            return None

    @staticmethod
    def send_to(socket_type, endpoint, py_obj):
        """

        :param socket_type:
        :param endpoint:
        :param py_obj:
        :return: Return True or Socket Object if not exists error, otherwise return None.
        """
        try:
            context = zmq.Context()
            socket = context.socket(socket_type)
            socket.connect(endpoint)
            socket.send_pyobj(py_obj)

            # REP zeromq socket type, always must response a message.
            if socket_type == zmq.REQ:
                receive_data = socket.recv_pyobj()
                print(receive_data)
                return receive_data
            else:
                return True

        except Exception as e:
            print("Exception-send_to ({0})".format(e.args))
            return None




