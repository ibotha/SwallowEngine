#include "swpch.hpp"
#include "Application.hpp"
extern Swallow::Application* Swallow::CreateApplication();

#if defined(SW_PLATFORM_WINDOWS) || defined(SW_PLATFORM_MACOSX)

int main(int argc, char **argv)
{
	Swallow::Log::Init();

	SW_CORE_WARN("Initialized Log");
	auto app = Swallow::CreateApplication();
	app->Run();
	delete app;
}

#endif