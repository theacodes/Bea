#pragma once

#include "GameObject.h"

class Cat
	: public bea::GameObject
{

public:

	Cat()
		: bea::GameObject(101), velocity()
	{
		// Make the sprite and such.
		makeSprite();
		sprite->setTexture( getRenderSystem().findTexture("fairy.png") );
		sprite->setFrameSize( phoenix::Vector2d(32,32) );
		sprite->setScale( phoenix::Vector2d( 1.5f, 1.5f ) );
		sprite->update();

		bea::SpriteAnimatorFrameRangePtr frame_animator( new bea::SpriteAnimatorFrameRange( sprite, 0, 3 ) );
		frame_animator->setSpeed( 5.0f/30.0f );


		// Make the collision object
		phoenix::Polygon poly(phoenix::Rectangle(0,0,32,32));
		makeCollisionObject(poly);

		// Set our position and velocity, randomly, of course.
		setPosition( phoenix::Vector2d( phoenix::random( 20, 800-20 ), phoenix::random( 20, 600-20 ) ) );
		velocity = phoenix::Vector2d( phoenix::random( 0, 90 ) - 45.0f, 0.0f );

		// rotate the sprite if we are walking left
		if( velocity.getX() < 0.0f ) sprite->setHorizontalFlip(true);
	}

	virtual void update( const double dtime = 0.0 ){
		setPosition( position+(
				velocity
				+phoenix::Vector2d(0.0f,90.0f)
		)*dtime);
	}

	virtual void draw( const double dtime = 0.0 ){
	}

	virtual void onCollision( bea::CollisionResult r ){
		setPosition( position  + r.separation*0.5f );
	}


protected:
	phoenix::Vector2d velocity;

};

