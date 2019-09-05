#include "SandboxApp.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"
#include "Swallow/AssetManager/AssetManager.hpp"

Sandbox::Sandbox() {
	Swallow::FlatColourMaterial::Init();
	Swallow::AssetManager::LoadObject("Skull", "Assets/Models/skull/skull.obj");
	Swallow::AssetManager::ListObjects();
	Swallow::AssetManager::ListMeshes("Skull");
	m_StartLayer = std::make_shared<StartLayer>();
	PushLayer(m_StartLayer);
}

Sandbox::~Sandbox() {
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}
