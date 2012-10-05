#pragma once

#include "Bea.h"
#include "Cat.h"


class BeaTestApplication
	: public bea::Application
{
public:

	virtual void onEvent( const bea::Event& e ){
		Application::onEvent(e);
	}

	virtual void onInit(){

		srand( (unsigned int) time(0) );

		system.setResizeBehavior( phoenix::RZB_EXPAND );
		phoenix::WindowManager::Instance()->setWindowSize(phoenix::Vector2d(800,600));

		new bea::DebugObject();

		phoenix::TexturePtr fairy = system.loadTexture("fairy.png");
		phoenix::TexturePtr tiles = system.loadTexture("tiles.png");

		//make cats
		for( int i = 0; i < 100; ++i ){
			new Cat();
		}

		//make level
		new bea::CollisionObject( collisions, phoenix::Polygon(phoenix::Rectangle(-30,0,50,600)), 100 );
		new bea::CollisionObject( collisions, phoenix::Polygon(phoenix::Rectangle(800-20,0,50,600)), 100 );
		new bea::CollisionObject( collisions, phoenix::Polygon(phoenix::Rectangle(0,600-20,800,50)), 100 );

		// Background
		phoenix::BatchGeometryPtr bg = new phoenix::BatchGeometry( system.getBatchRenderer(), phoenix::Rectangle(0,0,800,600) );
		bg->setDepth( -100.0f );
		bg->colorize( phoenix::Color( 189, 32, 32 ) );
		bg->update();

		//Tile map
		bea::MapLoader::load("test.tmx", boost::bind( &BeaTestApplication::onTileAdded, this, _1 ), boost::bind( &BeaTestApplication::onObjectAdded, this, _1 ) );

	}

	void onTileAdded( const bea::PropertyContainer& data ){
		if( data.contains("solid") && data.get<std::string>("solid") == "true" ){
			int x = data.get<int>("x");
			int y = data.get<int>("y");
			int w = data.get<int>("tile_width");
			int h = data.get<int>("tile_height");

			new bea::CollisionObject( collisions, phoenix::Polygon(phoenix::Rectangle( x*w,y*h, w,h )), 201 );
		}
	}

	void onObjectAdded( const bea::PropertyContainer& data ){
		int x = data.get<int>("x");
		int y = data.get<int>("y");
		int w = data.get<int>("width");
		int h = data.get<int>("height");

		new bea::CollisionObject( collisions, phoenix::Polygon(phoenix::Rectangle( x,y, w,h )), 202 );
	}


protected:
};