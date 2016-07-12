//
//  Publisher library on C++
//	
//  Diego R. Zagals <diegorz@me.com>
//

#include "zhelpers.hpp"

std::string convertToString(float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();   
}

void publishData(zmq::socket_t & socket, const char *topic){
	int64_t clock = s_clock();

	if (topic == "fridge"){
		temperatureDataBlockEvent t_data;
		t_data.absoluteDiff = (double) (within(100));
		t_data.status = ATREF;

		s_sendmore(socket, topic);
		s_sendmore(socket, convertToString(t_data.absoluteDiff));
    	s_sendmore(socket, convertToString(t_data.status));
    	s_send(socket, convertToString(clock));
    }

    if (topic == "antenna"){
		temperatureDataBlockEvent t_data;
		t_data.absoluteDiff = (double) (within(200));
		t_data.status = BELOWREF;

		s_sendmore(socket, topic);
		s_sendmore(socket, convertToString(t_data.absoluteDiff));
    	s_sendmore(socket, convertToString(t_data.status));
    	s_send(socket, convertToString(clock));
    }

    else
    	s_sendmore(socket, topic);
    	s_send(socket, convertToString(clock));
}

