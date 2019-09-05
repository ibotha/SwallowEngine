#pragma once

namespace Swallow
{
	class AudioAPI
	{
	public:
		enum class API
		{
			None = 0, OpenAL = 1
		};

	public:
		virtual void Init() = 0;

		inline static API GetAPI() { return s_API;  }

	private:
		static API s_API;
	};
}