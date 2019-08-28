#include "SandboxApp.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"

Sandbox::Sandbox() {
	Swallow::FlatColourMaterial::Init();
	m_StartLayer = std::make_shared<StartLayer>();
	PushLayer(m_StartLayer);
}

Sandbox::~Sandbox() {
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}
