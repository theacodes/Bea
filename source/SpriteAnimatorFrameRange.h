#ifndef __B_SPRITE_FRAME_RANGE_ANIMATOR__
#define __B_SPRITE_FRAME_RANGE_ANIMATOR__

#include "SpriteAnimator.h"

namespace bea{

/*
	Animates a sprites frame based on a range,
	for example frame 2 to 6.
*/
class SpriteAnimatorFrameRange
	: public SpriteAnimator
{

public:
	SpriteAnimatorFrameRange( SpritePtr _s, int _from = 0, int _to = 0 )
		: SpriteAnimator( _s ), from(_from), to(_to)
	{
	}

	virtual ~SpriteAnimatorFrameRange(){}

	virtual void update( int type ){
		if( type == 0 ){
			if( timer.getTime() > speed ){
				timer.reset();
				if( speed != 0.0f ) sprite->advanceFrame();
			}
		}

		// limit frames
		if( sprite->getFrame() > to || sprite->getFrame() < from ) sprite->setFrame( from );
	}

	void set( int _from, int _to ) { from = _from; to = _to; update(0); }
	void setFrom( int _from ) { from = _from; update(0); }
	void setTo( int _to ) { to = _to; update(0); }
	int getFrom(){ return from; }
	int getTo(){ return to; }

protected:
	int from;
	int to;

}; // class SpriteAnimatorFrameRange

typedef boost::intrusive_ptr<SpriteAnimatorFrameRange> SpriteAnimatorFrameRangePtr;

}; //namespace bea

#endif __B_SPRITE_FRAME_RANGE_ANIMATOR__