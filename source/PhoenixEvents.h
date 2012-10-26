#ifndef __BEA_PHOENIX_EVENTS_H__
#define __BEA_PHOENIX_EVENTS_H__

#include "Phoenix.h"
#include "EventListener.h"
#include <iostream>

namespace bea{

	//! Maps phoenix events to bea events.
	class PhoenixEventDispatch
	{

	public:
		PhoenixEventDispatch( )
			: windowconnection()
		{
			windowconnection = (phoenix::WindowManager::Instance())->
				listen( boost::bind( &PhoenixEventDispatch::onWindowEvent, this, _1 ) );
		}

		virtual ~PhoenixEventDispatch()
		{
			windowconnection.disconnect();
		}

		void onWindowEvent( phoenix::WindowEvent e )
		{
			bea::Event be;

			switch( e.type ){
				case phoenix::WET_UPDATE:
					be.name = std::string("phoenix:update");
					break;
				case phoenix::WET_CLOSE:
					be.name = std::string("phoenix:close");
					break;
				case phoenix::WET_MOVE:
					be.name = std::string("phoenix:move");
					be.properties["state"] = e.bool_data;
					break;
				case phoenix::WET_KEY:
					be.name = std::string("phoenix:key");
					be.properties["state"] = e.bool_data;
					be.properties["key"] = e.int_data;
					break;
				default:
					return;
			}

			bea::EventManager::getInstance()->signal_immediate( be );
		}

	private:

		boost::signals2::connection windowconnection;

	};

}; // namespace bea

#endif //__BEA_PHOENIX_EVENTS_H__