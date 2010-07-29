#ifndef __BEA_EVENT_LISTENER_H__
#define __BEA_EVENT_LISTENER_H__

#include <boost/shared_ptr.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/unordered_map.hpp>
#include <string>
#include "EventManager.h"

namespace bea
{

//! Class for listening to multiple events.
/*!
	Keeps track of connections forged for signals and ensures they're disconnected
	when this object is destroyed. Composition or private inheritance is suggested.
*/
class EventListener
{
private:

	//! Container of connections to manage.
	typedef boost::unordered_map< std::string, boost::signals2::connection > connections_map;
	connections_map connections;

public:

	EventListener() : connections() {}

	/*
		Disconnects all connections.
	*/
	virtual ~EventListener(){
		ignoreAll();
	}

	/*
		Listens for a particular event and manages the connection. Requires an
		EventManager, an Event 'type' (name), and a callback.
	*/
	inline void listen( EventManager* _m, const std::string& _n, const EventManager::event_signal::slot_type& _f ){
		connections[_n] = _m->listen( _n, _f );
	}

	/*
		Manages a connection
	*/
	inline void manage( const std::string& _n, boost::signals2::connection _c ){
		connections[_n] = _c;
	}

	/*
		Disconnects a particular event 'type' (name).
	*/
	inline void ignore( const std::string& _n ){
		connections[_n].disconnect();
		connections.erase(_n);
	}

	/*
		Disconnects all connections.
	*/
	inline void ignoreAll(){
		BOOST_FOREACH( connections_map::value_type i, connections ){
			i.second.disconnect();
		}
		connections.clear();
	}
};


} //namespace bea

#endif