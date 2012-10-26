#ifndef __BEA_APPLICATION_H__
#define __BEA_APPLICATION_H__

#include "Phoenix.h"
#include "EventManager.h"
#include "EventListener.h"
#include "Object.h"
#include "View.h"
#include "Sprite.h"
#include "PhoenixEvents.h"
#include "CollisionManager.h"

namespace bea{

class Application
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
	Application()
		: system(), events(), phoenixevents(), gametimer(), phoenixtimer(), objects(), game_update_interval(1.0/60.0), draw_update_interval(1.0/30.0)
	{
		instance = this;

		// Application event handler
		events.listen( "*", boost::bind( &Application::onEvent, this, _1 ) );
	}

	virtual ~Application(){
		instance = 0;
	}

	static Application* getInstance(){
		return instance;
	}

	inline phoenix::RenderSystem& getRenderSystem(){ return system; }
	inline EventManager& getEventManager(){ return events; }
	inline phoenix::ResourceManager& getObjectManager(){ return objects; }
	inline CollisionManager& getCollisionManager(){ return collisions; }

	void setGameUpdateInterval( double _i = 1.0/30.0 ){
		game_update_interval = _i;
	}

	void setDrawUpdateInterval( double _i = 1.0/30.0 ){
		draw_update_interval = _i;
	}

	virtual void onEvent( const bea::Event& e );

	virtual void onInit(){
	}

	virtual void onGameUpdate(){}

	virtual void onDrawUpdate(){}

	virtual void run();

	/* Global Variable Store*/
	static bea::PropertyContainer globals;

protected:
	phoenix::RenderSystem system;
	bea::EventManager events;
	phoenix::ResourceManager objects;
	CollisionManager collisions;

private: 
	bea::PhoenixEventDispatch phoenixevents;
	phoenix::Timer gametimer;
	phoenix::Timer phoenixtimer;
	double game_update_interval;
	double draw_update_interval;
	static Application* instance;
};

} // namespace bea

#endif //__BEA_APPLICATION_H__