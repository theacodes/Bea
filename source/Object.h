#ifndef __BEA_OBJECT_H__
#define __BEA_OBJECT_H__

#include "ObjectViewCommon.h"

namespace bea {

class Object
	: public bea::ObjectViewCommon
{
public:
	
	/*!
		Create a new object. This requires a resource manager, as
		objects are resources and are automatically managed.
		Optionally, you maybe specify the type number.
	*/
	Object( phoenix::ResourceManager& _rm, const int _t = 100 )
		: bea::ObjectViewCommon(_rm, _t)
	{
		listen( "game:update" );
		listen( "game:pause" );
		listen( "game:resume" );
	}

	virtual ~Object()
	{
	}
	
	/*!
		The base onEvent handler listens for and responds to 
		game:update, game:pause, and game:resume.  Derived classes,
		unless they'd like to handle those events themselves, should
		call this function at the beginning of their onEvent.
	*/
	virtual void onEvent( const bea::Event& e )
	{
		if( e.name == "game:update" ){
			if( ! timer.isPaused() ) {
				double dtime = timer.getTime();
				timer.reset();
				update( dtime );
			}
			return;
		}
		else if( e.name == "game:pause" ){
			timer.pause();
			return;
		}
		else if( e.name == "game:resume"){
			timer.resume();
			return;
		}
	}

	/*!
		The ever-important update function. The onEvent
		function automatically calls this when a game:update
		event is fired. All object updating code ( such as movement,
		etc. ) should go here.
	*/
	virtual void update( const double dtime = 0.0 ){}

};

typedef boost::intrusive_ptr<Object> ObjectPtr;

}//namespace bea.

#endif //__BEA_OBJECT_H__