#pragma once

#include "Swallow/Renderer/Renderer.hpp"
#include "CharMaterialInstance.hpp"
#include "Swallow/Renderer/Texture.hpp"

namespace Swallow
{
    class CharMaterial
    {
        public:
			static void Init();
        //     FlatColourMaterial();
        //     FlatColourMaterial(FlatColourMaterial const &rhs);
        //     FlatColourMaterial &operator=(FlatColourMaterial const &rhs);
        //     ~FlatColourMaterial();
			static Ref<CharMaterialInstance> Create();

		private:
			static Ref<Shader> m_Shader;
            static Ref<std::map<unsigned char, Ref<Character>>> m_Chars;
    };
}