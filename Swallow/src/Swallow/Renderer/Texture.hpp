#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

namespace Swallow {

	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		Texture2D();
		Texture2D(const Texture2D&);
		Texture2D &operator=(const Texture2D&);
		virtual ~Texture2D() = default;
		static Ref<Texture2D> Create(const std::string& path);
	};
	
	class Character : public Texture
	{
	public:
		virtual ~Character() = default;
		virtual uint32_t GetTop() const = 0;
		virtual uint32_t GetLeft() const = 0;
		static Ref<Character> Create(const FT_GlyphSlot);
	protected:

		Character() = default;
		Character(const Character&) = default;
		Character &operator=(const Character&) = default;
	};
}