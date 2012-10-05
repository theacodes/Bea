#ifndef __BEA_GAME_OBJECT_H__
#define __BEA_GAME_OBJECT_H__

#include "Object.h"
#include "Application.h"

namespace bea {

class GameObject
	: public bea::Object
{
public:
	
	/*!
		Create a new object.
	*/
	GameObject( const int _t = 200 )
		: bea::Object( Application::getInstance()->getObjectManager(), _t), draw_timer(), position(), sprite(), collision()
	{
		listen( "phoenix:update" );
	}

	virtual ~GameObject()
	{
	}

	inline void drop(){
		bea::Object::drop();
		if( collision ) collision->drop();
		if( sprite ) sprite->drop();
	}
	
	/*!
		The base onEvent handler listens for and responds to 
		phoenix:update, game:update, game:pause, and game:resume.  Derived classes,
		unless they'd like to handle those events themselves, should
		call this function at the beginning of their onEvent.
	*/
	virtual void onEvent( const bea::Event& e )
	{
		bea::Object::onEvent(e);
		
		if( e.name == "phoenix:update" ){
			double dtime = draw_timer.getTime();
			draw_timer.reset();
			draw( dtime );
		}
	}

	/*!
		automatically calls this when a game:update
		event is fired. All object updating code ( such as movement,
		etc. ) should go here.
	*/
	virtual void update( const double dtime = 0.0 ){}

	/*!
		automatically called with phoenix:update is fired.
	*/
	virtual void draw( const double dtime = 0.0 ){}


	/*! Base collision handler, just separates the object. Should usually be overloaded */
	virtual void onCollision( CollisionResult r ){

	}

	/*! Updates the internal position, but also the sprite and collision object's position */
	void setPosition(const phoenix::Vector2d& _p, const bool update = true ){
		position = _p;
		if( update ) updatePosition();
	}

	const phoenix::Vector2d& getPosition(){ return position; }

	/* Virtual, so you can overloads it an stuffs */
	virtual void updatePosition(){
		if( collision ) collision->getPolygon().setPosition(position);
		if( sprite ) sprite->setPosition(position);
	}


	/*! Creates a sprite, sets the internal sprite pointer, and returns it */
	SpritePtr makeSprite(){
		if( sprite ) sprite->drop();

		sprite = new bea::Sprite( Application::getInstance()->getObjectManager(), Application::getInstance()->getRenderSystem().getBatchRenderer() );
		return sprite;
	}

	/*! Creates a collision object, sets the internal collision pointer, listens for events, and returns it */
	CollisionObjectPtr makeCollisionObject(const phoenix::Polygon _p = phoenix::Polygon() ){
		if( collision ) collision->drop();

		collision = new CollisionObject( Application::getInstance()->getCollisionManager(), _p, getType() );
		manage( "collision", collision->listen( boost::bind( &GameObject::onCollision, this, _1 ) ) );
		return collision;
	}

	phoenix::RenderSystem& getRenderSystem(){
		return Application::getInstance()->getRenderSystem();
	}

protected:

	phoenix::Vector2d position;
	CollisionObjectPtr collision;
	SpritePtr sprite;

private:

	phoenix::Timer draw_timer;

};

typedef boost::intrusive_ptr<GameObject> GameObjectPtr;

}//namespace bea.

#endif //__BEA_GAME_OBJECT_H__