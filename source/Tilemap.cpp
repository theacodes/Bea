#include "Tilemap.h"
#include <fstream>

using namespace bea;
using namespace phoenix;
using namespace std;

Tilemap::Tilemap( phoenix::ResourceManager& _rmgr,
	phoenix::BatchRenderer& _r,
	const unsigned int _map_width, 
	const unsigned int _map_height, 
	const unsigned int _tile_width, 
	const unsigned int _tile_height,
	phoenix::TexturePtr _t )
	: phoenix::Resource( _rmgr, 30 ), tiles(),
	map_width( _map_width ), map_height( _map_height ),
	tile_width( _tile_width ), tile_height( _tile_height ),
	position(), geom(), scale(1.0f,1.0f)
{
	geom = new phoenix::BatchGeometry( _r, GL_QUADS, _t, 0, -99.0f );
	tiles.resize( map_width * map_height );
}

Tilemap::~Tilemap(){
}

void Tilemap::save( const std::string filename ){
	fstream file;
	file.open( filename.c_str(), fstream::out | fstream::binary );
	if( file.is_open() )
	{
		// header
		file<<char(5)<<char(29)<<char(90);
		// map size
		file.write( reinterpret_cast< char* >( &map_width ), sizeof(map_width) );
		file.write( reinterpret_cast< char* >( &map_height ), sizeof(map_height) );
		// tile size
		file.write( reinterpret_cast< char* >( &tile_width ), sizeof(tile_width) );
		file.write( reinterpret_cast< char* >( &tile_height ), sizeof(tile_height) );
		// tile data.
		for( unsigned int i = 0; i < tiles.size(); ++i ){
			file.write( reinterpret_cast< char* >( &tiles[i] ), sizeof(unsigned int) );
		}

		file.close();
	}
}

void Tilemap::load( const std::string filename ){
	fstream file;
	file.open( filename.c_str(), fstream::in | fstream::binary );
	if( file.is_open() )
	{
		// header
		char header[3];
		file.read( header, 3 );
		// map size
		file.read( reinterpret_cast< char* >( &map_width ), sizeof(map_width) );
		file.read( reinterpret_cast< char* >( &map_height ), sizeof(map_height) );
		tiles.resize( map_width * map_height );
		// tile size
		file.read( reinterpret_cast< char* >( &tile_width ), sizeof(tile_width) );
		file.read( reinterpret_cast< char* >( &tile_height ), sizeof(tile_height) );
		// tile data.
		for( unsigned int i = 0; i < tiles.size(); ++i ){
			file.read( reinterpret_cast< char* >( &tiles[i] ), sizeof(unsigned int) );
		}

		file.close();
	}
	update();
}

void Tilemap::setTile( unsigned int _x, unsigned int _y, unsigned int _t ){
	if( _x >= map_width ) _x = map_width-1;
	if( _y >= map_height ) _y = map_height-1;
	tiles[ (_y * map_width) + _x ] = _t;
}

unsigned int Tilemap::getTile( unsigned int _x, unsigned int _y ){
	if( _x >= map_width ) _x = map_width-1;
	if( _y >= map_height ) _y = map_height-1;
	return tiles[ (_y * map_width) + _x ];
}

void Tilemap::update(){
	geom->unlock(false);
	geom->clear();
	for( unsigned int y = 0; y < map_height; ++y ){
		for( unsigned int x = 0; x < map_width; ++x ){
			unsigned int tile = tiles[ (y * map_width) + x ];

			Vector2d position( (float) x * tile_width, (float) y * tile_height );

			// add the quad
			geom->addVertex( Vertex( position, Color() ) );
			geom->addVertex( Vertex( position + Vector2d(0,(float)tile_height), Color() ) );
			geom->addVertex( Vertex( position + Vector2d((float)tile_width,(float)tile_height), Color() ) );
			geom->addVertex( Vertex( position + Vector2d((float)tile_width,0), Color() ) );

			// set the tcoords
			calculateTCoords( tile, geom->getVertexCount()-4 );

		}
	}
	geom->scale( scale );
	geom->translate( position );
	geom->lock(true);
}

void Tilemap::updateTile( unsigned int _x, unsigned int _y ){
	if( geom->getVertexCount() == 0 ){
		update();
		return;
	}
	if( _x >= map_width ) _x = map_width-1;
	if( _y >= map_height ) _y = map_height-1;
	// set the tcoords
	calculateTCoords( tiles[ (_y * map_width) + _x ], ((_y * map_width) + _x) * 4 );
}

/*
	Set the tcoords for a specific piece of geometry.
*/
void Tilemap::calculateTCoords( unsigned int _tile, unsigned int _index )
{
	if( geom->getTexture() ){
		// Variables to be used to calculate the tcoords
		float twidth		= (float)geom->getTexture()->getWidth();
		float theight		= (float)geom->getTexture()->getHeight();
		int framesperrow	= int(twidth / tile_width);
		int xframe			= (_tile%framesperrow);
		int yframe			= (int)floor( float(_tile)/float(framesperrow) );

		// The tcoords
		float lowerx = (xframe*tile_width)/twidth;
		float upperx = ((xframe*tile_width) +tile_width)/twidth;
		float lowery = (yframe*tile_height)/theight;
		float uppery = ((yframe*tile_height) +tile_height)/theight;

		// Set them
		(*geom)[ _index ].tcoords = TextureCoords(lowerx,lowery);
		(*geom)[ _index+1 ].tcoords = TextureCoords(lowerx,uppery);
		(*geom)[ _index+2 ].tcoords = TextureCoords(upperx,uppery);
		(*geom)[ _index+3 ].tcoords =  TextureCoords(upperx,lowery);
	}
}