#include "SandboxApp.hpp"

Sandbox::Sandbox() {
	PushLayer(new StartLayer());
}

Sandbox::~Sandbox() {
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}
