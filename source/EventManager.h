#ifndef __B__EVENT_MANAGER__
#define __B__EVENT_MANAGER__

#include <boost/shared_ptr.hpp>
#include <boost/signals2/signal.hpp>
#include <deque>
#include <boost/bind.hpp>

#include "StringHash.h"
#include "PropertyContainer.h"
#include "Event.h"

namespace bea
{

class EventManager
{

public:

	//!Typedef for the signals
	typedef boost::signals2::signal<void (const Event&)>  event_signal;

private:

	//!Typdef for the container of signals.
	typedef boost::unordered_map< std::string, boost::shared_ptr<event_signal>, StringHash::hash_function, StringHash::equal_to> signal_map;

	//! container of signals.
	signal_map signals;

	//! Queue of events.
	std::deque< bea::Event > eventqueue;

	//! Pointer the global instance
	static EventManager* global_instance;

public:

	/*
		Creates a new event manager, it automatically sets
		the global instance to itself when created.
	*/
	EventManager()
		: signals(), eventqueue()
	{
		global_instance = this;
		// any event signal
		signals["*"] = boost::shared_ptr< event_signal >( new event_signal );
	}

	virtual ~EventManager(){}

	/*
		Set the pointer to the global instance.
	*/
	static void setInstance( EventManager* p ){
		global_instance = p;
	}

	/*
		Get the global instance.
	*/
	static EventManager* getInstance(){
		return global_instance;
	}

	/*
		Listen for a particular event. When the event fires, the callback function is called
		with a const bea::Event& as the first argument. You can use boost::bind to make the 
		callbacks. The "*" event is special, every event causes the "*" event to be signaled.
	*/
	boost::signals2::connection listen( const std::string& _n, const event_signal::slot_type& _s )
	{
		if( signals.find( _n ) == signals.end() )
			signals[_n] = boost::shared_ptr< event_signal >( new event_signal );

		return signals[_n]->connect( _s );
	}

	/*
		Processes all the events in the queue. The order is first in first out.
	*/
	void process(){
		while( ! eventqueue.empty() ){
			signal_immediate( eventqueue.front() );
			eventqueue.pop_front();
		}
	}

	/*
		Adds an event to the queue.
	*/
	inline void signal( const Event& _e )
	{
		eventqueue.push_back( _e );
	}

	/*
		Immediately signals an event.
	*/
	void signal_immediate( const Event& _e ){
		if( signals.find( _e.name ) != signals.end() )
			(*signals[ _e.name ])( _e );
		// any event signal
		(*signals["*"])(_e);
	}

};

}

#endif