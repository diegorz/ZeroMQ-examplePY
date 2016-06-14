#include "zmq.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

// Events

enum TemperatureStatus { OVERREF, ATREF, BELOWREF};

struct temperatureDataBlockEvent
{
	float absoluteDiff;
	TemperatureStatus status;
};

const std::string CHANNELNAME_FRIDGE = "fridge";
