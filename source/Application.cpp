#include "Application.h"

using namespace bea;

Application* Application::instance = 0;
bea::PropertyContainer Application::globals = bea::PropertyContainer();

void Application::onEvent( const bea::Event& e ){
	if( e.name == "phoenix:move" ){
		Event ev;
		if( e.properties.get<bool>("state") ){
			ev.name = std::string("game:pause");
		}
		else
		{
			ev.name = std::string("game:resume");
		}
		events.signal_immediate( ev );
	}
}


void Application::run(){
	onInit();

	gametimer.start();
	phoenixtimer.start();

	bool quit = false;
	while( !quit )
	{	

		// Game Loop
		if( gametimer.getTime() > game_update_interval ){
			gametimer.reset();

			// send update event.
			bea::Event updateevent;
			updateevent.name = std::string("game:update");
			events.signal_immediate( updateevent );

			onGameUpdate();

			
			collisions.update();

			events.process();
		}

		// Draw Loop
		if( phoenixtimer.getTime() > draw_update_interval ){
			phoenixtimer.reset();
			quit = !system.run();
			if( quit ){
				break;
			}

			onDrawUpdate();

			//fps
			///system.getDebugConsole()<<system.getFPS()<<"\n";

			// clean
			objects.clean();
		}
	}
}
