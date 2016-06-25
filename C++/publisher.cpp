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

#include "0mq_helper.hpp"

#define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))

int main (int argc, char *argv[]) {

    //  Prepare our context and publisher
    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUB);
    publisher.connect("tcp://localhost:5556");
    
    std::cout << "Sending updates ...\n" << std::endl;

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));

    while (1) {

        //int data;

        const char *filter = (argc > 1)? argv [1]: "fridge";
        
        //  Get values that will fool the boss
        /*if ( filter == CHANNELNAME_FRIDGE )
            data = within (215) - 80;

        else
            data = within (50) + 10;*/
    
        temperatureDataBlockEvent t_data;
        t_data.absoluteDiff = (double) (within(100));
        t_data.status = ATREF;

        //  Send message to all subscribers
        zmq::message_t message(20);
        /*snprintf ((char *) message.data(), 20 ,
            "%s %d", filter, data);
        publisher.send(message);*/

        snprintf ((char *) message.data(), 20 , 
            "%s %f %d", filter, t_data.absoluteDiff, t_data.status);

        publisher.send(message);

        //std::cout << "Send OK" << std::endl;
        
    }
    return 0;
}