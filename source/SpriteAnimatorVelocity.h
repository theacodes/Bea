#ifndef __B_SPRITE_VEL_ANIMATOR__
#define __B_SPRITE_VEL_ANIMATOR__

#include "SpriteAnimator.h"

namespace bea{

/*
	Animates a sprite's position based on a given velocity.
*/
class SpriteAnimatorVelocity
	: public SpriteAnimator
{

public:
	SpriteAnimatorVelocity( SpritePtr _s, const phoenix::Vector2d& _v = phoenix::Vector2d(0.0f,0.0f) )
		: SpriteAnimator( _s ), velocity(_v)
	{
	}

	virtual ~SpriteAnimatorVelocity(){}

	virtual void update( int type ){
		if( type == 0 ){
			double dt = timer.getTime();
			sprite->setPosition( sprite->getPosition() + ( velocity*(float)(dt) ) );
			timer.reset();
		}
	}

	void setVelocity( const phoenix::Vector2d& _v) { velocity = _v;}
	const phoenix::Vector2d& getVelocity(){ return velocity; }

protected:
	phoenix::Vector2d velocity;

}; // class SpriteAnimatorVelocity

typedef boost::intrusive_ptr<SpriteAnimatorVelocity> SpriteAnimatorVelocityPtr;

}; //namespace bea

#endif //__B_SPRITE_VEL_ANIMATOR__