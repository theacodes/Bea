#ifndef __PONG_VIEW_H__
#define __PONG_VIEW_H__

#include "ObjectViewCommon.h"
#include "Object.h"

namespace bea{

class View
	: public bea::ObjectViewCommon
{
public:

	/*!
		Create a new view. Views are attached to objects, so
		you must provide an object for the view to attach to.
		In the case of a 'dumb' view, you can create a 'dumb'
		stage object and attach views to that ( like score,
		etc. ). The view automatically adds itself to the same
		resource manager as the object. Optionally, you can
		provide a type number.
	*/
	View( ObjectPtr _p, const int _t = 101 )
		: ObjectViewCommon( _p->getResourceManager(), _t), obj(_p)
	{
		listen( "phoenix:update" );
	}

	virtual ~View()
	{
	}

	/*!
		The base onEvent handler listens for and responds to 
		phoenix:update.  Derived classes, unless they'd like to 
		handle that events themselves, should call this function 
		at the beginning of their onEvent.
	*/
	virtual void onEvent( const bea::Event& e ){

		if( e.name == "phoenix:update" ){
			double dtime = timer.getTime();
			if( obj->dropped() && !this->dropped() ){
				drop();
				return;
			}
			timer.reset();
			update( dtime );
		}
	}

	/*!
		Update behaves similar to it's Object counterpart, however
		there is one key difference: Views update on phoenix:update
		( page flip ), where Objects update on game:update ( whatever
		interval you signal that event ). This allows views to only
		redraw when phoenix needs them to redraw.
	*/
	virtual void update( const double dtime = 0.0 )
	{
	}

protected:
	ObjectPtr obj;

};

typedef boost::intrusive_ptr<View> ViewPtr;

} // namespace bea

#endif //__PONG_VIEW_H__