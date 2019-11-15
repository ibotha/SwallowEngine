#include "swpch.hpp"
#include "OpenALContext.hpp"

namespace Swallow
{
	OpenALContext::OpenALContext(ALCcontext *context)
		:m_Context(context)
	{
	}

	void OpenALContext::Init()
	{
		alcMakeContextCurrent(m_Context);
	}
} // namespace Swallow
