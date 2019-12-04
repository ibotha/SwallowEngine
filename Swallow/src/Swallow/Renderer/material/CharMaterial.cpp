#include "swpch.hpp"
#include "CharMaterial.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H

namespace Swallow
{

	Ref<Shader> CharMaterial::m_Shader;
    Ref<std::map<unsigned char, Ref<Character>>> CharMaterial::m_Chars = std::make_shared<std::map<unsigned char, Ref<Character>>>();
    bool once = true;
	void CharMaterial::Init()
	{

		std::string sVertexSrc = R"(
			#version 330 core
            layout (location = 0) in vec3 a_Position;
            layout (location = 1) in vec3 a_Normal;
            layout (location = 2) in vec2 a_TexCoords; // <vec2 pos, vec2 tex>
            out vec2 TexCoords;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

            void main()
            {
				gl_Position = (u_ViewProjection * u_Model) * vec4(a_Position, 1.0);
                TexCoords = a_TexCoords;
            }  
		)";

		std::string sFragmentSrc = R"(
            #version 330 core
            in vec2 TexCoords;
            out vec4 color;

            uniform sampler2D text;
            uniform vec4 textColor;

            void main()
            {    
                vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
                color = textColor * sampled;
            }
		)";
        // m_Shader.reset();
		m_Shader = Shader::Create(sVertexSrc, sFragmentSrc);

        // m_Chars->clear();
        FT_Library ft;
        FT_Face face;
        int error = FT_Init_FreeType(&ft);
        if (error)
        {
            SW_CORE_ASSERT(!error, "FreeType could not be initialised");
        }
        error = FT_New_Face(ft, "assets/Fonts/Arial.ttf", 0, &face);
        if (error)
        {
            SW_CORE_ASSERT(!error, "Arial font face could not be initialised");
        }
        FT_Set_Pixel_Sizes(face, 0, SW_FONT_RESOLUTION);
        for (unsigned char c = 0; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                SW_CORE_WARN("FreeType could not load character: {}", c);
                continue ;
            }
            m_Chars->insert(std::pair<unsigned char, Ref<Character>>(c, Character::Create(face->glyph)));
        }
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
	}

    Ref<CharMaterialInstance> CharMaterial::Create()
    {
		return std::make_shared<CharMaterialInstance>(m_Shader, m_Chars);
    }
}