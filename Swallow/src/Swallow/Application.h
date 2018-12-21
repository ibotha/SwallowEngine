#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Swallow {

	class SWALLOW_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application *CreateApplication();

}