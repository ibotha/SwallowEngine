#include "SandboxApp.hpp"

Sandbox::Sandbox() {
	m_StartLayer = std::make_shared<StartLayer>();
	PushLayer(m_StartLayer);
}

Sandbox::~Sandbox() {
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}
