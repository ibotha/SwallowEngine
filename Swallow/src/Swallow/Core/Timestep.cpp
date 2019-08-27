#include "swpch.hpp"
#include "Timestep.hpp"

namespace Swallow {
	Timestep::Timestep(float time)
			:m_Time(time)
	{
	}
	Timestep::~Timestep(){}
	Timestep::Timestep(const Timestep& cpy)
	{
		if (this != &cpy)
			*this = cpy;
	}
	Timestep &Timestep::operator=(const Timestep& rhs)
	{
		if (this != &rhs)
			this->m_Time = rhs.m_Time;
		return *this;
	}
}