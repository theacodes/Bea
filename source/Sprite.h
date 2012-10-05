#ifndef __BEA_SPRITE_H__
#define __BEA_SPRITE_H__

#include "phoenix.h"
#include "EventListener.h"

namespace bea{

class Sprite
	: public phoenix::Resource
{

public:

	/*! Signal used to fire events */
	typedef boost::signals2::signal< void (int) > SpriteSignal;

	Sprite( phoenix::ResourceManager& _rmgr, phoenix::BatchRenderer& _r );
	~Sprite();

	inline virtual void drop(){
		phoenix::Resource::drop();
		geom->drop();
	}

	/*! Listen to this sprites events, allows for animation, etc */
	virtual boost::signals2::connection connect( SpriteSignal::slot_type f ) { return subscribers.connect( f ); }

	virtual void onEvent( const bea::Event& e );

	virtual void update();

	inline void setPosition( const phoenix::Vector2d& _p ){ position = _p; }
	inline void setRotation( const float _t ) { rotation = _t; }
	inline void setScale( const phoenix::Vector2d& _s ){ scale = _s; }
	inline void setTexture( phoenix::TexturePtr _t ){ geom->setTexture( _t ); geom->update(); }
	inline void setFrameSize( const phoenix::Vector2d& _s ){ framesize = _s; }
	inline void setFrame( const int _f ){ frame = _f; }
	inline void setHorizontalFlip( const bool f ){ hflip = f; }
	inline void setVerticalFlip( const bool f ) { vflip = f; }
	
	inline void advanceFrame(){ frame = frame.get()+1; }

	inline phoenix::TexturePtr getTexture(){ return geom->getTexture(); }
	inline int getFrame(){ return frame; }
	inline const phoenix::Vector2d& getPosition(){ return position; }

protected:

	void calculateTextureCoords();

	SpriteSignal subscribers;

	bea::EventListener listener;
	phoenix::BatchGeometryPtr geom;

	phoenix::TrackingInvariant<phoenix::Vector2d> position;
	phoenix::TrackingInvariant<float> rotation;
	phoenix::TrackingInvariant<phoenix::Vector2d> scale;

	phoenix::TrackingInvariant<bool> hflip;
	phoenix::TrackingInvariant<bool> vflip;

	phoenix::Vector2d framesize;
	phoenix::TrackingInvariant<int> frame;

}; // class Sprite

typedef boost::intrusive_ptr<Sprite> SpritePtr;

}; // namespace bea


#endif //__BEA_SPRITE_H__