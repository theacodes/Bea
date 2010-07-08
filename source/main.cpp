#include <iostream>
#include "PropertyContainer.h"

#include "EventManager.h"

using namespace std;
using namespace bea;


void showEvent( const Event& e ){
	std::cout<<"Event Name: "<<e.name<<std::endl;
	std::cout<<"Event Properties: "<<std::endl;
	e.properties.dump();
}

int main()
{

    PropertyContainer properties;
    properties["Greeting"] = string("Hello, World!");
    properties.dump();

	//make an event manager
	EventManager emgr;
	

	vector< boost::signals2::connection > connections;
	connections.push_back( emgr.listen("Test Event", &showEvent) );

	BOOST_FOREACH( boost::signals2::connection& c, connections )
		c.disconnect();
	connections.clear();

	//make an event
	Event ev;
	ev.name = string("Test Event");
	ev.properties["id"] = 5;
	ev.properties["dude"] = string("no way");

	std::cout<<std::endl<<"Signaling: "<<std::endl;
	emgr.signal(ev);

    cin.get();
    return 0;
}