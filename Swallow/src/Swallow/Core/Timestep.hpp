#pragma once

namespace Swallow {
	class Timestep
	{
	public:
		Timestep(float time = 0.0f);
		Timestep(const Timestep&);
		~Timestep();
		Timestep &operator=(const Timestep&);

		inline float GetSeconds() const { return m_Time; }
		inline float GetMiliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}