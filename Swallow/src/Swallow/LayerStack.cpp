#include "swpch.hpp"
#include "LayerStack.hpp"

namespace Swallow {
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
	}

	void LayerStack::PushLayer(Ref<Layer> layer)
	{
		layer->OnAttach();
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex++, layer);
	}

	void LayerStack::PushOverlay(Ref<Layer> layer)
	{
		layer->OnAttach();
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Ref<Layer> layer)
	{
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
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
		}
	}
}