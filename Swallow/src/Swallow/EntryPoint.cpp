#include "swpch.hpp"
#include "Application.hpp"
extern Swallow::Application* Swallow::CreateApplication();

#if defined(SW_PLATFORM_WINDOWS) || defined(SW_PLATFORM_MACOSX)

int main(int argc, char **argv)
{
	static_cast<void>(argc);
	static_cast<void>(argv);
	Swallow::Log::Init();
	hi:
	auto app = Swallow::CreateApplication();
	app->hasnt_given_up = false;
	app->Run();
	if (app->hasnt_given_up)
	{
		goto hi;
	}
	delete app;
}

#endif