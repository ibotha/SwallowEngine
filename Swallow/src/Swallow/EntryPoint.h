#pragma once

#include "Application.h"

#ifdef SW_PLATFORM_WINDOWS

extern Swallow::Application* Swallow::CreateApplication();

int main(int argc, char **argv)
{
	auto app = Swallow::CreateApplication();
	app->Run();
	delete app;
}

#endif