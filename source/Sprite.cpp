#include "Sprite.h"

using namespace phoenix;
using namespace bea;

/*
	Creation
*/
Sprite::Sprite( phoenix::ResourceManager& _rmgr, phoenix::BatchRenderer& _r )
: Resource(_rmgr, 10), listener(), geom(), position(), rotation(0), scale( Vector2d(1,1) ), framesize( Vector2d(16,16) ), frame(0), hflip(false), vflip(false)
{
	geom = new BatchGeometry( _r, Rectangle( Vector2d(0,0), framesize ) );

	listener.listen( EventManager::getInstance(), "phoenix:update", boost::bind( &Sprite::onEvent, this, _1 ) );
}

/*
	Destruction
*/
Sprite::~Sprite(){
}

/*
	Event Handler
*/
void Sprite::onEvent( const bea::Event& e ){
	if( e.name == "phoenix:update" ){
		update();
	}
}

/*
	Calculates Texture Coordinates
*/
void Sprite::calculateTextureCoords(){
	if( geom->getTexture() && geom->getTexture()->getWidth() > 0.0f && geom->getTexture()->getHeight() > 0.0f && geom->getVertexCount() == 4 ){

		// Variables to be used to calculate the tcoords
		float twidth		= (float)geom->getTexture()->getWidth();
		float theight		= (float)geom->getTexture()->getHeight();
		int framesperrow	= int(twidth / framesize.getX());
		int xframe			= (frame.get()%framesperrow);
		int yframe			= (int)floor( float(frame.get())/float(framesperrow) );

		// The tcoords
		float lowerx = (xframe*framesize.getX())/twidth;
		float upperx = ((xframe*framesize.getX()) +framesize.getX())/twidth;
		float lowery = (yframe*framesize.getY())/theight;
		float uppery = ((yframe*framesize.getY()) +framesize.getY())/theight;

		// assign them
		(*geom)[0].tcoords.u = lowerx;
		(*geom)[0].tcoords.v = lowery;
		(*geom)[1].tcoords.u = lowerx;
		(*geom)[1].tcoords.v = uppery;
		(*geom)[2].tcoords.u = upperx;
		(*geom)[2].tcoords.v = uppery;
		(*geom)[3].tcoords.u = upperx;
		(*geom)[3].tcoords.v = lowery;

		// hflip and vflip
		if( hflip.get() ){
			(*geom)[0].tcoords.u = upperx;
			(*geom)[1].tcoords.u = upperx; 
			(*geom)[2].tcoords.u = lowerx;
			(*geom)[3].tcoords.u = lowerx;
		}
		if( vflip.get() ){
			(*geom)[0].tcoords.v = uppery; 
			(*geom)[1].tcoords.v = lowery; 
			(*geom)[2].tcoords.v = lowery; 
			(*geom)[3].tcoords.v = uppery; 
		}
	}
}

/*
	Geometry Updater
*/
void Sprite::update(){

	subscribers( 0 );

	// If the invariant broke, update the geometry.
	if( ! (position.check() && rotation.check() && scale.check()) ){
		position.reset();
		rotation.reset();
		scale.reset();

		//initial state
		geom->fromRectangle( Rectangle( Vector2d(0,0), framesize ) );
		// center geometry
		geom->translate( -(framesize/2.0f) );
		// scale
		geom->scale( scale );
		// rotate
		geom->rotate( rotation.get() );
		// translate
		geom->translate( position );

		// calculate those texture coordinates.
		calculateTextureCoords();
	}

	// Update the texture coordinates
	if( ! (frame.check() && hflip.check() && vflip.check()) ){
		frame.reset();
		hflip.reset();
		vflip.reset();
		calculateTextureCoords();
	}
}