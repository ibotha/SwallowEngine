#include "swpch.hpp"
#include "AssestManager.hpp"

AssestManager::AssestManager()
{

	m_Textures = new HashMap<std::string, bool>();
	m_Models = new HashMap<std::string, bool>();
	m_Sounds = new HashMap<std::string, bool>();
	m_Misc = new HashMap<std::string, bool>();
}

AssestManager::~AssestManager()
{
	delete m_Textures;
	delete m_Models;
	delete m_Sounds;
	delete m_Misc;
}

void AssestManager::addResource(ResourceType type, std::string name, bool value)
{
	switch (type)
	{
	case ResourceType::NONE:
	default:
		break;
	case ResourceType::TEXTURES:
		m_Textures->put(name, value);
		break;
	case ResourceType::MODELS:
		m_Models->put(name, value);
		break;
	case ResourceType::SOUNDS:
		m_Sounds->put(name, value);
		break;
	case ResourceType::MISC:
		m_Misc->put(name, value);
		break;
	}
}

template<typename T>
T* AssestManager::findResource<T>(ResourceType type, std::string name)
{
	return nullptr;
	switch (type)
	{
	case ResourceType::NONE:
	default:
		return nullptr;
	case ResourceType::TEXTURES:
		return (void*)m_Textures->get<std::string, T>(name);
	case ResourceType::MODELS:
		return (void*)m_Models->get<std::string, T>(name);
	case ResourceType::SOUNDS:
		return (void*)m_Sounds->get<std::string, T>(name);
	case ResourceType::MISC:
		return (void*)m_Misc->get<std::string, T>(name);
	}
}
