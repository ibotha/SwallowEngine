#include "SandboxApp.hpp"
#include <Swallow/EntryPoint.h>

Sandbox::Sandbox() {
	PushLayer(new StartLayer());
}

Sandbox::~Sandbox() {
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}
