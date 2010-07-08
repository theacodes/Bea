#ifndef __B_APP_STATE_MANAGER_H__
#define __B_APP_STATE_MANAGER_H__

#include "phoenix.h"

namespace bea{

class AppState;

class AppStateManager
	: public phoenix::ResourceManager
{

public:
	AppStateManager()
		: phoenix::ResourceManager()
	{
	}

	virtual ~AppStateManager()
	{}

	virtual void change( boost::intrusive_ptr<AppState> _s );

	virtual boost::intrusive_ptr<AppState> getCurrent(){
		return current;
	}

	virtual void run();

private:
	boost::intrusive_ptr<AppState> current;
};

} // namespace bea

#include "AppState.h"

#endif __B_APP_STATE_MANAGER_H__