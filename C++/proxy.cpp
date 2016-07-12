//
//  Proxy example on C++
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