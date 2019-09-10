#include "AnimationController.hpp"
#define ONGOING_KEYFRAME 0
#define NEXT_KEYFRAME 1
#define LAST_KEYFRAME 2

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
		m_AdvanceTimer += deltaTime;
		
		if (m_AdvanceTimer >= m_KeyFrames.size() - 1)
			m_AdvanceTimer = 0;
        
        return 0;
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
        return Swallow::AssetManager::FetchObject(m_BaseObjectName, m_KeyFrames[static_cast<int>(m_AdvanceTimer)])->GetVertexBuffers()[0];
    }

    Ref<VertexBuffer> AnimationController::GetVertexBuffer2()
    {
        return Swallow::AssetManager::FetchObject(m_BaseObjectName, m_KeyFrames[static_cast<int>(m_AdvanceTimer) + 1])->GetVertexBuffers()[0];
    }
    
}