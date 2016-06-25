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
