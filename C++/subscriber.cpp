//
//  Subscriber example on C++  
//	based Weather update client created by
//	Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

//  Connects SUB socket to tcp://localhost:5558 (Backend)
//  Collects updates and calculates avg 
//
//  Diego R. Zagals <diegorz@me.com>
//

#include "subscriber.hpp"

int main (int argc, char *argv[])
{
    zmq::context_t context (1);

    //  Socket to talk to server
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5558");

    //  Subscribe to some event type
	const char *filter = (argc > 1)? argv [1]: "clock";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen (filter));    


    std::cout << "Collecting updates from publishers of event type: " << filter << "\n" << std::endl;

    while (1){
        /*std::string channel_name;
        double data = 0.0;
        int status = 0;*/

        receiveData(subscriber);
    }
          
    return 0;
}

