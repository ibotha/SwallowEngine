#include "AnimationController.hpp"
#define ONGOING_KEYFRAME 0
#define NEXT_KEYFRAME 1
#define LAST_KEYFRAME 2

namespace Swallow
{
	
	AnimationController::AnimationController(const std::string & assignedName)
	{
        m_advanceTimer = 0;
		base = assignedName;
		return;
	}

    int AnimationController::Advance(float advanceTimer)
    {
        //if (static_cast<int>(m_advanceTimer) <= static_cast<int>(m_advanceTimer + advanceTimer))
        //{
		m_advanceTimer += advanceTimer;
		SW_CORE_INFO("We are updating the animation timer: {}", m_advanceTimer);

		if (m_advanceTimer >= keyFrames.size() - 1)//Never goes beyond the keyframe size/limit
			m_advanceTimer = 0;//Goes back to keyframe 0 and counts to the heightest possble keyframe;
            //if (m_advanceTimer > keyFrames.size())
                //state = LAST_KEYFRAME;
            //else
                //state = NEXT_KEYFRAME;
        //}
        //else
        //{
            //state = ONGOING_KEYFRAME;
            //ResetAnimationLoop();
        //}
        
        return 0;//state;
    }

    Ref<AnimationController> AnimationController::Create(const std::string & assignedName)
    {
		return std::make_shared<AnimationController>(assignedName);//std::make_shared<AnimationController>(whats_my_type);
    }

    /*
    void AnimationController::Create(std::string assignedName)
    {
        base = assignedName;
        SW_CORE_INFO("Get's Here: {}", "");
    }
    */

    void AnimationController::AddKeyFrame(std::string object_Name)
    {
        keyFrames.push_back(object_Name);
    }

    void AnimationController::ResetAnimationLoop()
    {
        m_advanceTimer = 0;
    }

    Ref<VertexBuffer> &AnimationController::GetVB1()
    {
        return Swallow::AssetManager::FetchObject(base, keyFrames[static_cast<int>(m_advanceTimer)])->GetVertexBuffers()[0];
    }

    Ref<VertexBuffer> &AnimationController::GetVB2()
    {
        return Swallow::AssetManager::FetchObject(base, keyFrames[static_cast<int>(m_advanceTimer) + 1])->GetVertexBuffers()[0];
    }

    /*
        m_Pillarnimation = Swallow::AnimationController::Create("Pillar");
        m_PillarAnimation->AddKeyFrame("Cube");
        m_PillarAnimation->AddKeyFrame("Cube.001");
        m_PillarAnimation->AddKeyFrame("Cube.002");
        m_PillarAnimation->AddKeyFrame("Cube.003");
        m_PillarAnimation->AddKeyFrame("Cube.004");
    */

    /*
        if (m_PillarAnimation->Advance(1 * ts.GetSeconds()))
        {
            m_StateAnimationTest2->GetVertexArray()->GetVertexBuffers().clear();
            auto [buffer1, buffer2] = m_PillarAnimation->GetBuffers();
            m_StateAnimationTest2->GetVertexArray()->AddVertexBuffer(buffer1);
            m_StateAnimationTest2->GetVertexArray()->AddVertexBuffer(buffer2);
        }
    */
}