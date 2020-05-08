#pragma once
#include "Texture.hpp"

namespace Swallow {

	class SubTexture2D {
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		static Ref<SubTexture2D> CreateFromTilePallet(Ref<Texture2D> texture, const glm::ivec2& pos, const glm::ivec2& size, const glm::ivec2& tileSize, const glm::ivec2& margin);

		inline Ref<Texture2D> GetTexture() { return m_Texture; }
		inline const glm::vec2* GetCoords() { return m_Coords; }
	private:
		Ref<Texture2D> m_Texture;
		glm::vec2 m_Coords[4];
	};
}