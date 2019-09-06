#include "SandboxApp.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"
#include "Swallow/Renderer/material/CharMaterial.hpp"

Sandbox::Sandbox() {
	Swallow::FlatColourMaterial::Init();
	Swallow::CharMaterial::Init();
	m_StartLayer = std::make_shared<StartLayer>();
	PushLayer(m_StartLayer);
}

Sandbox::~Sandbox() {
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}
