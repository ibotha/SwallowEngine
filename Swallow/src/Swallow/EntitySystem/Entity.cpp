#include <swpch.hpp>
#include "Entity.h"
#include "Component.h"

namespace Swallow {

	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
	}

	void Entity::Update(const Timestep& ts)
	{
		for (auto& component : m_Components)
			component->Update(ts);
	}

}