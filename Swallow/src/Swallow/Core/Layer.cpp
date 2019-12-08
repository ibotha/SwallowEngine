#include "swpch.hpp"
#include "Layer.hpp"

namespace Swallow {
	Layer::Layer(const std::string& name)
		:m_DebugName(name)
	{
		SW_PROFILE_FUNCTION();
	}

	Layer::~Layer()
	{
		SW_PROFILE_FUNCTION();
	}
}