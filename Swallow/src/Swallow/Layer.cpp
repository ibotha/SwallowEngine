#include "swpch.hpp"
#include "Layer.hpp"

namespace Swallow {
	Layer::Layer(const std::string& name)
		:m_DebugName(name)
	{
	}

	void Layer::OnAttach()
	{

	}

	void Layer::OnDetach()
	{

	}

	void Layer::OnUpdate(Timestep timestep)
	{
		static_cast<void>(timestep);
	}

	void Layer::OnImGuiRender()
	{

	}

	void Layer::OnEvent(Event &e)
	{
		static_cast<void>(e);
	}

	Layer::~Layer()
	{
	}
}