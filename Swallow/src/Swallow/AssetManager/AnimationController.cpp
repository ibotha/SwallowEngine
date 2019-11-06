#include "AnimationController.hpp"

namespace Swallow
{
	
	AnimationController::AnimationController(const std::string & assignedName)
	{
        m_AdvanceTimer = 0;
		m_BaseObjectName = assignedName;
		return;
	}

    int AnimationController::Advance(float deltaTime)
    {
        int first = m_AdvanceTimer;
		m_AdvanceTimer += deltaTime;
        int  second = m_AdvanceTimer;
		
		if (m_AdvanceTimer >= m_KeyFrames.size())
        {
            return LAST_KEYFRAME;
        }
        if (first != second)
            return NEXT_KEYFRAME;
        
        return ONGOING_KEYFRAME;
    }

    Ref<AnimationController> AnimationController::Create(const std::string & assignedName)
    {
		return std::make_shared<AnimationController>(assignedName);
    }

    void AnimationController::AddKeyFrame(std::string keyframeName)
    {
        m_KeyFrames.push_back(keyframeName);
    }

    Ref<VertexBuffer> AnimationController::GetVertexBuffer1()
    {
        SW_INFO("{}, {}", (static_cast<int>(m_AdvanceTimer) % m_KeyFrames.size()), ((static_cast<int>(m_AdvanceTimer) + 1) % m_KeyFrames.size()));
        return Swallow::AssetManager::FetchObject(m_BaseObjectName, m_KeyFrames[static_cast<int>(m_AdvanceTimer) % m_KeyFrames.size()])->GetVertexBuffers()[0];
    }

    Ref<VertexBuffer> AnimationController::GetVertexBuffer2()
    {
        return Swallow::AssetManager::FetchObject(m_BaseObjectName, m_KeyFrames[(static_cast<int>(m_AdvanceTimer) + 1) % m_KeyFrames.size()])->GetVertexBuffers()[0];
    }
    
}