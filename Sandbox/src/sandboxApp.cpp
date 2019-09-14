#include "SandboxApp.hpp"

Sandbox::Sandbox() {
	m_StartLayer = std::make_shared<Layer2D>();
	PushLayer(m_StartLayer);
}

Sandbox::~Sandbox() {
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}
