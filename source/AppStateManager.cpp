#include "AppStateManager.h"

void bea::AppStateManager::change( boost::intrusive_ptr<AppState> _s ){
	current = _s;
}

void bea::AppStateManager::run(){
	lock();
	BOOST_FOREACH( phoenix::ResourcePtr r, getList() )
	{
		boost::intrusive_ptr<AppState> s = r->grab<bea::AppState>();
		s->run();
	}
	unlock();
	clean();
}