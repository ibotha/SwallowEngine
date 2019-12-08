#include "swpch.hpp"
#include "LayerStack.hpp"

namespace Swallow {
	LayerStack::LayerStack()
	{
		SW_PROFILE_FUNCTION();
	}

	LayerStack::~LayerStack()
	{
		SW_PROFILE_FUNCTION();
	}

	void LayerStack::PushLayer(Ref<Layer> layer)
	{
		SW_PROFILE_FUNCTION();
		layer->OnAttach();
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex++, layer);
	}

	void LayerStack::PushOverlay(Ref<Layer> layer)
	{
		SW_PROFILE_FUNCTION();
		layer->OnAttach();
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Ref<Layer> layer)
	{
		SW_PROFILE_FUNCTION();
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Ref<Layer> layer)
	{
		SW_PROFILE_FUNCTION();
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
		}
	}
}