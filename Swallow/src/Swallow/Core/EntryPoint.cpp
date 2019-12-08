#include "swpch.hpp"
#include "Application.hpp"
extern Swallow::Application* Swallow::CreateApplication();

#if defined(SW_PLATFORM_WINDOWS) || defined(SW_PLATFORM_MACOSX)

int main(int argc, char **argv)
{
	SW_PROFILE_BEGIN_SESSION("StartUp", "Swallow-Startup-profile.json");
	Swallow::Log::Init();
	auto app = Swallow::CreateApplication();
	SW_PROFILE_END_SESSION();


	SW_PROFILE_BEGIN_SESSION("Runtime", "Swallow-Runtime-profile.json");
	app->Run();
	SW_PROFILE_END_SESSION();

	SW_PROFILE_BEGIN_SESSION("ShutDown", "Swallow-Shutdown-profile.json");
	delete app;
	SW_PROFILE_END_SESSION();
}

#endif