#ifndef __BEA_OBJECTVIEWCOMMON_H__
#define __BEA_OBJECTVIEWCOMMON_H__

#include "phoenix.h"
#include "EventListener.h"
#include "globals.h"

namespace bea {

/*!
	Views and Objects have a lot in common, this is just an application
	of DRY so that they can use common functionality together.
	Functionality provided:
		listen( string eventname )	- listens for an event for onEvent.
		signal( event )				- Signals the global event manager.
		onEvent( event )			- Event callback. (pure virtual)
		update( time )				- Update process. (puer virtual)
		proected object timer		- Keeps track of time between update() calls.

*/
class ObjectViewCommon
	: public phoenix::Resource, public bea::EventListener
{
public:
	
	/*!
		Derived classes should pass in a resource manager to
		be automatically managed.
	*/
	ObjectViewCommon( phoenix::ResourceManager& _rm, const int _t = 99 )
		: Resource(_rm, _t), listener(), timer()
	{
	}

	virtual ~ObjectViewCommon()
	{
	}

	/*!
		Overloaded drop() immediately disconnects all signals.
		It's suggested that derived classes call this function.
	*/
	virtual void drop(){
		phoenix::Resource::drop();
		listener.ignoreAll();
	}

	/*!
		Listens for an event from the global event manager
		on the default 'onEvent' handler, you may also call 
		bea::EventListener::listen to pass custom callbacks for 
		events or use a different event manager.
	*/
	void listen( const std::string& _n ){
		listener.listen( EventManager::getInstance(), _n, boost::bind( &ObjectViewCommon::onEvent, this, _1 ) );
	}

	/*!
		Signals an event through the global event manager.
	*/
	void signal( const bea::Event& e ){
		EventManager::getInstance()->signal( e );
	}
	
	/*!
		The base onEvent handler listens for and responds to 
		game:update, game:pause, and game:resume.  Derived classes,
		unless they'd like to handle those events themselves, should
		call this function at the beginning of their onEvent.
	*/
	virtual void onEvent( const bea::Event& e ) = 0;

	/*!
		The ever-important update function. Should be called
		by on event, but the event that triggers it is different
		for Views and Objects.
	*/
	virtual void update( const double dtime = 0.0 ) = 0;

protected:
	phoenix::Timer timer;

private:
	EventListener listener;
	

};

}//namespace bea.

#endif //__BEA_OBJECTVIEWCOMMON_H__