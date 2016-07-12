//
//	0mq_helper   
//
//  Diego R. Zagals <diegorz@me.com>
//

#include "zmq.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

// Events
enum TemperatureStatus { OVERREF, ATREF, BELOWREF };

struct temperatureDataBlockEvent
{
	float absoluteDiff;
	TemperatureStatus status;
};

const std::string CHANNELNAME_FRIDGE = "fridge";

//  Provide random number from 0..(num-1)
#define within(num) (int) ((float) (num) * random () / (RAND_MAX + 1.0))

//  Receive 0MQ string from socket and convert into string
static std::string
s_recv (zmq::socket_t & socket) {

    zmq::message_t message;
    socket.recv(&message);

    return std::string(static_cast<char*>(message.data()), message.size());
}

//  Convert string to 0MQ string and send to socket
static bool
s_send (zmq::socket_t & socket, const std::string & string) {

    zmq::message_t message(string.size());
    memcpy (message.data(), string.data(), string.size());

    bool rc = socket.send (message);
    return (rc);
}

//  Sends string as 0MQ string, as multipart non-terminal
static bool
s_sendmore (zmq::socket_t & socket, const std::string & string) {

    zmq::message_t message(string.size());
    memcpy (message.data(), string.data(), string.size());

    bool rc = socket.send (message, ZMQ_SNDMORE);
    return (rc);
}
