#ifndef __BEA_EVENT_SPY_H__
#define __BEA_EVENT_SPY_H__

#include <iostream>
#include "EventListener.h"

namespace bea{


	/*
		Prints all events to stdout.
	*/
	class EventSpy
		: public EventListener
	{

	public:
		
		EventSpy( EventManager* _mgr )
		{
			listen( _mgr, "*", boost::bind(&EventSpy::onEvent, this, _1) );
		}

		virtual ~EventSpy()
		{}

		virtual void onEvent( Event e )
		{
			std::cout<<"Event "<<e.name<<" signaled"<<std::endl;
		}

	private:

	};


}; // Namespace bea


#endif //__BEA_EVENT_SPY_H__