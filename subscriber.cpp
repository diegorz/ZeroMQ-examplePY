//
//  Update client example in C++ 
//	based Weather update client created by
//	Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

//  Connects SUB socket to tcp://localhost:5556 (Backend)
//  Collects updates and finds avg temp in zipcode
//
//  Diego R. Zagals <diegorz@me.com>
//
#include "0mq_helper.hpp"

int main (int argc, char *argv[])
{
    //char name_events[3] = {'temperature','humidity','dewpoint'};
    
    zmq::context_t context (1);

    //  Socket to talk to server
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5558");

    //  Subscribe to some event type
	const char *filter = (argc > 1)? argv [1]: "Weather";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen (filter));

    std::cout << "Collecting updates from server...\n" << std::endl;
    
    //  Process 100 updates
    int update_nbr;
    long total_temp = 0, total_hum = 0;

    for (update_nbr = 0; update_nbr < 100; update_nbr++) {

        zmq::message_t update;

        int temperature, relhumidity;
        std::string channel_name;
        
        subscriber.recv(&update);

        //std::cout << subscriber.recv(&update) << std::endl;

        std::istringstream iss(static_cast<char*>(update.data()));
		iss >> channel_name >> temperature >> relhumidity ;

		total_temp += temperature;
        total_hum += relhumidity;

        //std::cout << zipcode << std::endl;
    }
    std::cout 	<< "The '"<< filter
    			<<"' was "<<(int) (total_temp / update_nbr) <<" C"
                << " and "<<(int) (total_hum / update_nbr) <<" %"
    			<< std::endl;

            
    return 0;
}
