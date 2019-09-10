#include "swpch.hpp"
#include "AnimationMaterial.hpp"

namespace Swallow
{
	Ref<Shader> AnimationMaterial::m_Shader;

	void AnimationMaterial::Init()
	{
		m_Shader = Shader::Create("assets/shaders/AnimationShader.glsl");
	}

    Ref<AnimationMaterialInstance> AnimationMaterial::Create()
    {
		return std::make_shared<AnimationMaterialInstance>(m_Shader);
    }
}