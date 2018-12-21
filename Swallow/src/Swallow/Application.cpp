#include "Application.h"

#include "Swallow/Events/ApplicationEvent.h"
#include "Swallow/Log.h"

namespace Swallow {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent c(1200, 300);
		SW_TRACE(c.ToString());

		while (true)
		{

		}
	}
}
