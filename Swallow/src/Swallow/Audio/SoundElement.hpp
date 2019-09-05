#pragma once

#include <glm.hpp>

namespace Swallow
{
	struct SoundElement
	{
		unsigned int	Buffer;
		unsigned int	Source;
		unsigned int	Channels;
		unsigned int	Bps;
		unsigned int	Format;
		glm::vec3		Vel;
		glm::vec3		Pitch;
		glm::vec3		Up;
		glm::vec3		At;
	};
}
