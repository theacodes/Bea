#ifndef __BEA_MAPLOADER_H__
#define __BEA_MAPLOADER_H__

#include "boost/function.hpp"
#include "boost/foreach.hpp"
#include "phoenix.h"
#include "Tilemap.h"
#include "PropertyContainer.h"
#include "Application.h"

namespace bea{

/* Tiled Map Loader, has limits and such */
class MapLoader
{

public:

	typedef boost::function< void( const bea::PropertyContainer& )> callback;

	static const bool load( const std::string filename, MapLoader::callback tile_callback = MapLoader::callback(), MapLoader::callback object_callback = MapLoader::callback() );


protected:

	

	/*! Creates a new tilemap
		@param _map_width, _map_height The size (in tiles) of the map.
		@param _tile_width, _tile_height The size (in pixels) of each tile.
		@param _t The texture to look at tiles.
	*/
	MapLoader();


}; // class MapLoader

}; //namespace bea

#endif //__BEA_MAPLOADER_H__