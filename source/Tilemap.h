#ifndef __BEA_TILEMAP_H__
#define __BEA_TILEMAP_H__

#include "phoenix.h"

namespace bea{

class Tilemap 
	: public phoenix::Resource
{

public:

	/*! Creates a new tilemap
		@param _map_width, _map_height The size (in tiles) of the map.
		@param _tile_width, _tile_height The size (in pixels) of each tile.
		@param _t The texture to look at tiles.
	*/
	Tilemap( phoenix::ResourceManager& _rmgr, 
		phoenix::BatchRenderer& _r,
		const unsigned int _map_width = 256, 
		const unsigned int _map_height = 256, 
		const unsigned int _tile_width = 16, 
		const unsigned int _tile_height = 16,
		phoenix::TexturePtr _t = phoenix::TexturePtr() );

	virtual ~Tilemap();

	inline virtual void drop(){
		phoenix::Resource::drop();
		geom->drop();
	}

	/*! Save the entire map to a file */
	void save( const std::string filename );

	/*! Load the entire map from a file, loads map size and tile size as well as tile data */
	void load( const std::string filename );

	void setTile( unsigned int _x, unsigned int _y, unsigned int _t );
	unsigned int getTile( unsigned int _x, unsigned int _y );

	inline void setTexture( phoenix::TexturePtr _t ){ geom->setTexture(_t); geom->update(); }
	inline phoenix::TexturePtr getTexture( ) { return geom->getTexture(); }

	inline void setMapSize( unsigned int _w, unsigned int _h ){ map_width = _w; map_height = _h; tiles.resize( map_width * map_height ); }
	inline void setTileSize( unsigned int _w, unsigned int _h ){ tile_width = _w; tile_height = _h; }
	inline unsigned int getMapWidth(){ return map_width; }
	inline unsigned int getMapHeight(){ return map_height; }
	inline unsigned int getTileWidth(){ return tile_width; }
	inline unsigned int getTileHeight(){ return tile_height; }

	inline void setPosition( const phoenix::Vector2d& _p = phoenix::Vector2d( 0,0 ) ) { position = _p; }
	inline const phoenix::Vector2d& getPosition() { return position; }

	inline void setScale( const phoenix::Vector2d& _s = phoenix::Vector2d( 1,1 ) ) { scale = _s; }
	inline const phoenix::Vector2d& getScale() { return scale; }

	inline void setDepth( const float d = -99.0f ){ geom->setDepth( d ); geom->update(); }
	inline const float getDepth(){ return geom->getDepth(); }

	/*! Updates the geometry buffer, must be called whenever you're done updating tiles. */
	virtual void update();

	/*! Updates a single tile in the geometry buffer. */
	virtual void updateTile(  unsigned int _x, unsigned int _y );

protected:

	void calculateTCoords( unsigned int _tile, unsigned int _index );

	std::vector<unsigned int> tiles;
	unsigned int map_width, map_height;
	unsigned int tile_width, tile_height;
	phoenix::Vector2d position;
	phoenix::Vector2d scale;
	phoenix::BatchGeometryPtr geom;

}; // class Tilemap

typedef boost::intrusive_ptr<Tilemap> TilemapPtr;

}; //namespace bea

#endif //__BEA_TILEMAP_H__