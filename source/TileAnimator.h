#ifndef __BEA_TILE_ANIM_H__
#define __BEA_TILE_ANIM_H__

#include "phoenix.h"
#include "Tilemap.h"

namespace bea{

/*
	A simple time-and-range-based tile animator.
*/
class TileAnimator
	: public phoenix::Resource
{
public:
	TileAnimator( TilemapPtr _m, unsigned int _tx = 0, unsigned int _ty = 0, unsigned int _s = 0, unsigned int _e = 0 )
		: phoenix::Resource( _m->getResourceManager() ), tilemap( _m ), updateconnection(), speed(0.0f), tilex(_tx), tiley(_ty), start(_s), end(_e)
	{
		updateconnection = EventManager::getInstance()->listen( "phoenix:update", boost::bind(&TileAnimator::update, this, _1) );
		timer.start();
	}

	virtual ~TileAnimator(){
		updateconnection.disconnect();
	}

	virtual void update( const bea::Event& e ){
		if( timer.getTime() > speed ){
			timer.reset();
			if( speed != 0.0f ){
				tilemap->setTile( tilex, tiley, tilemap->getTile( tilex, tiley ) + 1 );
				tilemap->updateTile( tilex, tiley );
			}
		}
		if( tilemap->getTile( tilex, tiley ) > end || tilemap->getTile( tilex, tiley ) < start ){
			tilemap->setTile( tilex, tiley, start );
			tilemap->updateTile( tilex, tiley );
		}
	}

	inline const float getSpeed() const { return speed; }
	inline void setSpeed( const float _s ) { speed = _s; }

	void set( int _s, int _e ) { start = _s; end = _e; update( bea::Event() ); }
	void setStart( int _s ) { start = _s; update( bea::Event() ); }
	void setEnd( int _e ) { end = _e; update( bea::Event() ); }
	int getStart(){ return start; }
	int getEnd(){ return end; }

protected:
	TilemapPtr tilemap;
	boost::signals2::connection updateconnection;
	phoenix::Timer timer;
	float speed;
	unsigned int tilex, tiley, start, end;

}; // class spriteanimator

typedef boost::intrusive_ptr<TileAnimator> TileAnimatorPtr;

}; //namespace bea

#endif //__BEA_TILE_ANIM_H__