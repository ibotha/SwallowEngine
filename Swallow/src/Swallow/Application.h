#pragma once

#include "Core.h"

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