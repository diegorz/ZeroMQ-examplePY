//
//  Update server example in C++ 
//	based on Weather update server created by
//	Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//
//  Binds PUB socket to tcp://*:5556
//  Publishes random updates
//
//  Diego R. Zagals <diegorz@me.com>
//
#include "0mq_helper.hpp"

#define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))

int main (int argc, char *argv[]) {

    //  Prepare our context and publisher
    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUB);
    publisher.bind("tcp://*:5556");
    
    std::cout << "Sending updates ...\n" << std::endl;

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));

    while (1) {

        int temperature, relhumidity;

        const char *filter = (argc > 1)? argv [1]: "Weather";
        
        //  Get values that will fool the boss
        temperature = within (215) - 80;
        relhumidity = within (50) + 10;

        //  Send message to all subscribers
        zmq::message_t message(20);
        snprintf ((char *) message.data(), 20 ,
            "%s %d %d", filter, temperature, relhumidity);
        publisher.send(message);

        //std::cout << "Filter: " << sensor << " Temperature: " << temperature << " and Humidity: "<< relhumidity << std::endl;
        
    }
    return 0;
}