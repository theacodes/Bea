#include "AppStateManager.h"

void bea::AppStateManager::run(){
	lock();
	BOOST_FOREACH( phoenix::ResourcePtr r, getList() )
	{
		boost::intrusive_ptr<AppState> s = r->grab<bea::AppState>();
		if( s && !s->dropped() ){
			s->run();
		}
	}
	unlock();
	clean();
}