#pragma once

#include <Swallow/Core/Timestep.hpp>

namespace Swallow {
	class Component;

	class Entity {
	public:

		Entity();
		~Entity();

		void Update(const Timestep& ts);

		template<class T, class ...Args, std::enable_if_t<std::is_base_of<Component, T>::value>* = nullptr>
		Ref<T> AddComponent(Args&&... args) {
			Ref<T> component = CreateRef<T>(std::forward<Args>(args)...);
			m_Components.push_back(component);
			m_Components.back()->Init();
			m_Components.back()->SetEntity(this);
			return component;
		}

		glm::vec3 pos = {0,0,0};
		glm::vec3 scale = { 1,1,1 };
		glm::vec3 rotation = {0, 0, 0};

	private:
		std::vector<Ref<Component>> m_Components;
	};

}