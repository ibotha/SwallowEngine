#include "SandboxApp.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"
#include "Swallow/AssetManager/AssetManager.hpp"

Sandbox::Sandbox() {
	Swallow::FlatColourMaterial::Init();
	Swallow::AssetManager::LoadObject("asdasd", "asdasdas");
	m_StartLayer = std::make_shared<StartLayer>();
	PushLayer(m_StartLayer);
}

Sandbox::~Sandbox() {
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}
