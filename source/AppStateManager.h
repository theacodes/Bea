#ifndef __B_APP_STATE_MANAGER_H__
#define __B_APP_STATE_MANAGER_H__

#include "Phoenix.h"

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
	{
		clear();
	}

	virtual void run();

private:
};

} // namespace bea

#include "AppState.h"

#endif __B_APP_STATE_MANAGER_H__