#pragma once

#include <Swallow/Core/Timestep.hpp>
#include "Entity.h"

namespace Swallow {

	class Component {
	public:
		Component(const std::string& name): m_Name(name) {}
		virtual void Init() {}

		virtual void Update(const Timestep& ts) {}

		virtual std::string GetName() { return m_Name; }

		inline void SetEntity(Entity* e) { m_Entity = e; }
		inline Entity* GetEntity() { return m_Entity; }

	private:
		std::string m_Name;
		Entity* m_Entity;
	};

}