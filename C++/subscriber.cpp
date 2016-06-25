//
//  Subscriber example on C++  
//	based Weather update client created by
//	Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

//  Connects SUB socket to tcp://localhost:5558 (Backend)
//  Collects updates and calculates avg 
//
//  Diego R. Zagals <diegorz@me.com>
//

#include "0mq_helper.hpp"

int main (int argc, char *argv[])
{
    zmq::context_t context (1);

    //  Socket to talk to server
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5558");

    //  Subscribe to some event type
	const char *filter = (argc > 1)? argv [1]: "fridge";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen (filter));

    std::cout << "Collecting updates from publishers...\n" << std::endl;
    
    //  Process 100 updates
    /*int update_nbr;
    long total_data = 0;
    std::string channel_name;

    for (update_nbr = 0; update_nbr < 100; update_nbr++) {

        zmq::message_t update;
        
        subscriber.recv(&update);

        std::istringstream iss(static_cast<char*>(update.data()));
        iss >> channel_name >> data;
        
        //std::cout << "String Separado OK" << std::endl;

        total_data += data;

    }*/  


    while (1){
        std::string channel_name;
        double data = 0.0;
        int status = 0;

        zmq::message_t update;

        subscriber.recv(&update);
        std::istringstream iss(static_cast<char*>(update.data()));
        iss >> channel_name >> data >> status;

        if ( filter == channel_name){
        std::cout << "The '"<< channel_name
        << " is "<< data <<" units "
        << " and status " << status << std::endl;
        }

    }


    /*if ( strcmp(filter,"fridge") == 0 ){
        std::cout   << "The '"<< channel_name
        << " was "<<(int) (total_data / update_nbr) <<"C"
        << std::endl;
    }

    else{
        std::cout   << "The '"<< channel_name
        << " was "<<(int) (total_data / update_nbr) <<"%"
        << std::endl;
    }*/

            
    return 0;
}

