#ifndef __BEA_SPRITE_ANIM_H__
#define __BEA_SPRITE_ANIM_H__

#include "phoenix.h"
#include "Sprite.h"

namespace bea{

/*
	Interface for sprite animators.
*/
class SpriteAnimator
	: public phoenix::Resource
{
public:
	SpriteAnimator( SpritePtr _s )
		: phoenix::Resource( _s->getResourceManager() ), sprite( _s ), spriteconnection(), speed(0.0f)
	{
		spriteconnection = _s->connect( boost::bind(&SpriteAnimator::update, this, _1) );
		timer.start();
	}

	virtual ~SpriteAnimator(){
		spriteconnection.disconnect();
	}

	virtual void update( int type ){};

	inline const float getSpeed() const { return speed; }
	inline void setSpeed( const float _s ) { speed = _s; }

protected:
	SpritePtr sprite;
	boost::signals2::connection spriteconnection;
	phoenix::Timer timer;
	float speed;

}; // class spriteanimator

typedef boost::intrusive_ptr<SpriteAnimator> SpriteAnimatorPtr;

}; //namespace bea

#endif //__BEA_SPRITE_ANIM_H__