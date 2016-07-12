//
//  Publisher example on C++
//	based on Weather update server created by
//	Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//
//  Connect PUB socket to tcp://localhost:5556 (Frontend)
//  Publishes random updates
//
//  Diego R. Zagals <diegorz@me.com>
//

#include "publisher.hpp"

//#define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))

int main (int argc, char *argv[]) {

    //  Prepare our context and publisher
    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUB);
    publisher.connect("tcp://localhost:5556");
    
    std::cout << "Sending updates ...\n" << std::endl;

    while (1) {

        if (argc > 1){
            for (int i=1; i<argc; i++){

                const char *event_type = argv[i];

                std::cout << "TOPIC: " << event_type << std::endl;

                //  Send message to all subscribers
                publishData(publisher,event_type);

            }
        }

        else{
            const char *event_type = "clock";
            
            //  Send message to all subscribers
            publishData(publisher,event_type);
            std::cout << "TOPIC: " << event_type << std::endl;
        }
    }

    return 0;
}