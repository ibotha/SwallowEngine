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
		virtual void SetPosition(const glm::vec3& pos) = 0;
		virtual void SetVelocity(const glm::vec3& vel) = 0;
		virtual void SetGain(float gain) = 0;
		virtual void SetAt(const glm::vec3& at) = 0;
		virtual void SetUp(const glm::vec3& up) = 0;

		inline static API GetAPI() { return s_API;  }

	private:
		static API s_API;
	};
}