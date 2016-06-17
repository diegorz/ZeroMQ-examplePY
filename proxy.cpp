//
//  Proxy example device C++ for ACS
//	based in Weather proxy created by
//	Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//
// 	Diego R. Zagals <diegorz@me.com>
//
#include "0mq_helper.hpp"

int main (int argc, char *argv[])
{
	zmq::context_t context(1);

    //  This is where the server sits
    zmq::socket_t frontend (context, ZMQ_SUB);
    frontend.bind("tcp://*:5556");

    //  Subscribe on everything
    frontend.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    
    //  This is our public endpoint for subscribers
    zmq::socket_t backend (context, ZMQ_PUB);
    backend.bind("tcp://*:5558");

    //  Run the proxy until the user interrupts us 
    try {
        std::cout << "Starting Proxy...\n" << std::endl;
        zmq::proxy(static_cast<void *>(frontend), static_cast<void *> (backend), NULL);
    }
    catch (std::exception &e){
        std::cout << "Error in Proxy : " << e.what() << std::endl;
    }
    
    return 0;
}

    /*//  Shunt messages out to our own subscribers
    while (1) {
        while (1) {
            zmq::message_t message;
            int more;
            size_t more_size = sizeof (more);

            //  Process all parts of the message
            frontend.recv(&message);
            frontend.getsockopt( ZMQ_RCVMORE, &more, &more_size);
            backend.send(message, more? ZMQ_SNDMORE: 0);
            if (!more)
                std::cout << "No more messages...\n" << std::endl;
                break;      //  Last message part
        }
    }
    return 0;
}*/
