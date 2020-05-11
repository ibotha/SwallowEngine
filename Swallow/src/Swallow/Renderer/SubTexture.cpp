#include <swpch.hpp>
#include "SubTexture.h"

namespace Swallow {
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
	{
		m_Texture = texture;
		m_Coords[0] = { min.x, min.y };
		m_Coords[1] = { max.x, min.y };
		m_Coords[2] = { max.x, max.y };
		m_Coords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromTilePallet(Ref<Texture2D> texture, const glm::ivec2& pos, const glm::ivec2& size, const glm::ivec2& tileSize, const glm::ivec2& margin)
	{
		glm::vec2 min = {
			pos.x * (tileSize.x + margin.x),
			pos.y * (tileSize.y + margin.y)
		};

		glm::vec2 max = {
			min.x + tileSize.x + (tileSize.x + margin.x) * (size.x - 1),
			min.y + tileSize.y + (tileSize.y + margin.y) * (size.y - 1)
		};

		glm::vec2 div = { (float)texture->GetWidth(), (float)texture->GetHeight() };

		min /= div;
		max /= div;

		return CreateRef<SubTexture2D>(texture, min, max);
	}
}
