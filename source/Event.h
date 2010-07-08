#ifndef __B__EVENT_CONSTRUCT__
#define __B__EVENT_CONSTRUCT__

#include <string>
#include "PropertyContainer.h"

namespace bea
{

/*
	Bea's generic event container. The name is the only
	defining characteristic of the event, every event
	'type' (name) should have 0 or more associated properties
	that contain event data.
*/
struct Event
{
	std::string name;
	PropertyContainer properties;
};

}

#endif