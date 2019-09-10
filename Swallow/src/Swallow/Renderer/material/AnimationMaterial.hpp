#pragma once

#include "Swallow/Renderer/Renderer.hpp"
#include "AnimationMaterialInstance.hpp"

namespace Swallow
{
    class AnimationMaterial
    {
        public:
			static void Init();
        //     AnimationMaterial();
        //     AnimationMaterial(AnimationMaterial const &rhs);
        //     AnimationMaterial &operator=(AnimationMaterial const &rhs);
        //     ~AnimationMaterial();
			static Ref<AnimationMaterialInstance> Create();

		private:
			static Ref<Shader> m_Shader;
    };
}