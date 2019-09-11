#include "SandboxApp.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"
#include "Swallow/Renderer/material/CharMaterial.hpp"
#include "Swallow/Renderer/material/AnimationMaterial.hpp"
#include "Swallow/AssetManager/AssetManager.hpp"

Sandbox::Sandbox() {
	Swallow::FlatColourMaterial::Init();
	Swallow::AnimationMaterial::Init();
	Swallow::CharMaterial::Init();
	Swallow::AssetManager::LoadObject("Car", "Assets/Models/Lamborginhi/Lamborghini_Aventador.obj");
	Swallow::AssetManager::LoadObject("Pillar", "Assets/Models/Twiting/Twiting.obj");
	Swallow::AssetManager::LoadObject("Torus", "Assets/Models/Twiting/Twiting2.obj");
	Swallow::AssetManager::ListObjects();
	Swallow::AssetManager::ListMeshes("Pillar");
	m_StartLayer = std::make_shared<StartLayer>();
	PushLayer(m_StartLayer);
}

Sandbox::~Sandbox() {
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}
