//
//  Subscriber library on C++
//  Diego R. Zagals <diegorz@me.com>
//

#include "zhelpers.hpp"


void receiveData(zmq::socket_t & socket){
	std::cout << "----------------------------------------" << std::endl;

    while (1) {
        //  Process all parts of the message
        zmq::message_t message;
        socket.recv(&message);

        //  Dump the message as text or binary
        int size = message.size();
        std::string data(static_cast<char*>(message.data()), size);

        bool is_text = true;

        int char_nbr;
        unsigned char byte;
        for (char_nbr = 0; char_nbr < size; char_nbr++) {
            byte = data [char_nbr];
            if (byte < 32 || byte > 127)
                is_text = false;
        }
        std::cout << "[" << std::setfill('0') << std::setw(3) << size << "]";
        for (char_nbr = 0; char_nbr < size; char_nbr++) {
            if (is_text)
                std::cout << (char)data [char_nbr];
            else
                std::cout << std::setfill('0') << std::setw(2)
                   << std::hex << (unsigned int) data [char_nbr];
        }
        std::cout << std::endl;

        int more = 0;           //  Multipart detection
        size_t more_size = sizeof (more);
        socket.getsockopt (ZMQ_RCVMORE, &more, &more_size);
        
        if (!more){
        	std::stringstream ss;
    	
    	    ss.clear();
        	ss.str(data);
        	int64_t clock;
        	assert ((ss >> clock));
       		
       		double time_dif = s_clock () - clock ;
            // Suicide snail logic
            if ( time_dif > MAX_ALLOWED_DELAY) {
                std::cerr << "E: subscriber cannot keep up, aborting " << time_dif << std::endl;
             	break;
    		}	
        }

        // Work for 1 msec plus some random additional time
        //s_sleep(1000*(1+within(2)));
	}
}