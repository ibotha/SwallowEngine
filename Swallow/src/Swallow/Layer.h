#pragma once

#include "Swallow/Core.h"
#include "Events/Event.h"

namespace Swallow {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event &e) {}

		inline const std::string& GetName() const { return m_DebugName; }

	private:
		const std::string m_DebugName;
	};
}