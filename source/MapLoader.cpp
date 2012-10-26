#include "Tmx.h"
#include "MapLoader.h"

using namespace bea;

const bool MapLoader::load( const std::string filename, MapLoader::callback tile_callback, MapLoader::callback object_callback ){
	auto app = Application::getInstance();
	Tmx::Map map;

	map.ParseFile(filename);

	if( map.HasError() ){
		app->getRenderSystem().getDebugConsole()<<"\n"<<"Error Loading "<<filename<<": "<<map.GetErrorText();
		return false;
	}

	// Load all of the tilesets
	boost::unordered_map< std::string, phoenix::TexturePtr > tileset_textures;
	for (int i = 0; i < map.GetNumTilesets(); ++i) {
		const Tmx::Tileset *tileset = map.GetTileset(i);

		auto t = app->getRenderSystem().loadTexture( tileset->GetImage()->GetSource() );

		tileset_textures.insert( std::pair<std::string, phoenix::TexturePtr>( tileset->GetName(), t) );

		app->getRenderSystem().getDebugConsole()<<"\n"<<"Loaded tileset texture "<<tileset->GetImage()->GetSource()<<" for "<<tileset->GetName();
	}

	// Go through each layer
	for (int i = 0; i < map.GetNumLayers(); ++i) {
		const Tmx::Layer *layer = map.GetLayer(i);
		bea::TilemapPtr tiles = 0;

		for (int x = 0; x < layer->GetWidth(); ++x) {
			for (int y = 0; y < layer->GetHeight(); ++y) {
				auto tile_id = layer->GetTileId(x, y);
				if( tile_id == 0 ) continue;

				const Tmx::Tileset *tileset = map.FindTileset(tile_id);
				if( tileset == 0 ) continue;

				// Create the tileset when we get to the first tile in the map 
				if( !tiles ){
					tiles = new bea::Tilemap( 
						app->getObjectManager() , 
						app->getRenderSystem().getBatchRenderer(), 
						layer->GetWidth(), layer->GetHeight(),
						tileset->GetTileWidth(), tileset->GetTileHeight(),
						tileset_textures[tileset->GetName()]
					);
					app->getRenderSystem().getDebugConsole()<<"\n"<<"Added tilemap layer "<<layer->GetName()<<" with tileset "<<tileset->GetName()<<" W:"<<tiles->getMapWidth()<<" H:"<<tiles->getMapHeight();
				}

				// finally, set the tile
				tile_id -= tileset->GetFirstGid();
				if(tiles) tiles->setTile( x, y, tile_id );

				// callback
				if( tile_callback ){
					bea::PropertyContainer props;
					props["id"] = tile_id;
					props["tilemap"] = tiles;
					props["x"] = x;
					props["y"] = y;
					props["layer"] = layer->GetName();
					props["tile_width"] = tileset->GetTileWidth();
					props["tile_height"] = tileset->GetTileHeight();

					auto tile = tileset->GetTile(tile_id);
					if( tile != 0 ){
						auto tile_props = tile->GetProperties();
						if( !tile_props.Empty() ){
							auto list = tile_props.GetList();
							for( auto pit = list.begin(); pit != list.end(); ++pit ){
								props[ pit->first ] = pit->second;
							}
						}
					}

					tile_callback(props);
				}
			}
		}
		
		if( tiles ) {
			tiles->setDepth( tiles->getDepth() + (float(i)/10.0f) );
			tiles->update();
		}
	}

	// Go through the object groups
	if( object_callback ){

		for (int i = 0; i < map.GetNumObjectGroups(); ++i) {
			const Tmx::ObjectGroup *objectGroup = map.GetObjectGroup(i);
			for (int j = 0; j < objectGroup->GetNumObjects(); ++j) {

				const Tmx::Object *object = objectGroup->GetObject(j);

				bea::PropertyContainer props;
				props["name"] = object->GetName();
				props["group"] = objectGroup->GetName();
				props["type"] = object->GetType();
				props["x"] = object->GetX();
				props["y"] = object->GetY();
				props["width"] = object->GetWidth();
				props["height"] = object->GetHeight();

				auto obj_props = object->GetProperties();
				if( !obj_props.Empty() ){
					auto list = obj_props.GetList();
					for( auto pit = list.begin(); pit != list.end(); ++pit ){
						props[ pit->first ] = pit->second;
					}
				}

				object_callback(props);
			}
		}
	}

	return true;
}