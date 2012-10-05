#ifndef __PONG_COLLISION_OBJ_H__
#define __PONG_COLLISION_OBJ_H__

#include "phoenix.h"
#include "CollisionManager.h"

namespace bea{

//! Simple class to provide collidable objects & callbacks.
class CollisionObject
	: public phoenix::Resource
{

public:

	//! Collision signal type
	typedef boost::signals2::signal<void (const CollisionResult&)>  CollisionSignal;

	CollisionObject( CollisionManager& _cm, const phoenix::Polygon _p, int _t = 0 )
		: Resource( _cm, _t ), persistent( false ), polygon( _p ), velocity()
	{}

	virtual ~CollisionObject(){}

	//! Listens to Collision Events.
	/*!
		By forging a connection here, your listener will receive all collision events. The
		listener is responsible for handling the connection (that means closing it when
		the listener is destructed).
	*/
	boost::signals2::connection listen( const CollisionSignal::slot_type& _s )
	{
		return collision_signal.connect( _s );
	}

	//! Passes an event through the event signal.
	/*!
		Called by the collision manager.
	*/
	void signal( const CollisionResult& r ){
		if( !dropped() ){
			collision_signal( r );
		}
	}

	inline phoenix::Polygon& getPolygon() { return polygon; }
	inline void setPolygon( const phoenix::Polygon& _p ){ polygon = _p; }
	
	inline const phoenix::Vector2d& getVelocity(){ return velocity; }
	inline void setVelocity( const phoenix::Vector2d& _v ){ velocity = _v; }

	/*!
		Setting the protected attribute has no collision-related effect
		on the object, but may be used by the application
		to preserve objects between rooms.
	*/
	bool isPersistent() { return persistent; }
	void setPersistent( const bool p ){ persistent = p; }

private:
	bool persistent;
	phoenix::Polygon polygon;
	phoenix::Vector2d velocity;
	CollisionSignal collision_signal;
};

typedef boost::intrusive_ptr<CollisionObject> CollisionObjectPtr;

}; //namespace bea

#endif //__PONG_COLLISION_OBJ_H__