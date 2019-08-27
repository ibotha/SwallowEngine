#pragma once
#include "HashMap.hpp"

#include "swpch.hpp"

enum ResourceType
{
	NONE = 0,
	TEXTURES,
	MODELS,
	SOUNDS,
	MISC
};

class AssestManager
{
public:
	AssestManager();
	AssestManager(const AssestManager&) = default;
	AssestManager &operator=(const AssestManager&) = default;
	~AssestManager();

	void* findResource(ResourceType, std::string, bool);
	void	addResource(ResourceType, std::string, bool);

private:
	HashMap<std::string, bool>* m_Textures;
	HashMap<std::string, bool>* m_Models;
	HashMap<std::string, bool>* m_Sounds;
	HashMap<std::string, bool>* m_Misc;
};

