#ifndef __B_APP_STATE__
#define __B_APP_STATE__

#include <string>
#include "phoenix.h"

#include "EventListener.h"
#include "AppStateManager.h"

namespace bea{

class AppState
	: public phoenix::Resource
{
public:

	AppState( AppStateManager& s, const std::string _n )
		: phoenix::Resource(s), name(_n)
	{}

	virtual ~AppState(){
	}

	AppStateManager& getStateManager(){
		return dynamic_cast<AppStateManager&>(getResourceManager());
	}

	/*!
		Overloaded drop() immediately disconnects all signals.
		It's suggested that derived classes call this function.
	*/
	virtual void drop(){
		phoenix::Resource::drop();
		listener.ignoreAll();
		if( getStateManager().getCurrent() == this ){
			getStateManager().change( boost::intrusive_ptr<AppState>() );
		}
	}

	/*
		Changes the active state the the given state, and then
		drops this state. This effectively hands off execution to
		a completely new state.
	*/
	virtual void change( boost::intrusive_ptr<AppState> _s ){
		getStateManager().change(_s);
		drop();
	}

	/*
		This activates this state as the currently active state
		in the state manager.
	*/
	virtual void activate(){
		getStateManager().change( this );
	}

	/*
		Behaves just like ObjectViewCommon::listen
	*/
	void listen( const std::string& _n ){
		listener.listen( EventManager::getInstance(), _n, boost::bind( &AppState::onEvent, this, _1 ) );
	}

	/*
		Behaves just like ObjectViewCommon::onEvent
	*/
	virtual void onEvent( const bea::Event& e ){};

	/*
		Runs the state, happens at the same time as game:update usually.
	*/
	virtual void run(){
	}

	inline const std::string& getName(){ return name; }

private:
	std::string name;
	bea::EventListener listener;
};

typedef boost::intrusive_ptr<AppState> AppStatePtr;

} //namespace bea

#endif; //__B_APP_STATE__