#ifndef __BEA_DBGOBJ_
#define __BEA_DBGOBJ_

#include "GameObject.h"

namespace bea{

class DebugObject 
	: public GameObject
{

public:

	DebugObject()
		: GameObject(), active(false)
	{
		listen("phoenix:key");
	}


	virtual void onEvent( const Event& e ){
		GameObject::onEvent(e);

		if( e.name == "phoenix:key" ){
			if( e.properties.get<int>("key") == '/' ){
				if( e.properties.get<bool>("state") ) active = !active;
			}
		}
	}


	virtual void draw(const double dtime){
		if( active ){
			// Stats
			getRenderSystem().getDebugConsole()<<"\n"<<dtime<<"s | "<<getRenderSystem().getFPS()<<" FPS | "<<  Application::getInstance()->getCollisionManager().getTestsCount() << " Collisions";

			// Collision objects.
			BOOST_FOREACH( phoenix::ResourcePtr r, Application::getInstance()->getCollisionManager().getList() ){
				if( !r->dropped() ){
					bea::CollisionObjectPtr c = r->grab<bea::CollisionObject>();
					float hue = r->getType() * 0.618033988749895f;
					hue = fmod( hue, 1.0f );
					getRenderSystem().drawPolygon( c->getPolygon(), bea::hsv( hue, 0.5f, 0.95f, 0.3f ) );
				}
			}
		}
	}

protected:
	bool active;
};

} // namespace bea

#endif;