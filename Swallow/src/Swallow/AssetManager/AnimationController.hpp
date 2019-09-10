#pragma once
#include "GameObject.hpp"
#include "AssetManager.hpp"

namespace Swallow {

    class AnimationController
    {
    public:
        AnimationController(const std::string &name);
        AnimationController &operator=(const AnimationController&) = default;
        AnimationController(const AnimationController&) = default;
        
        static Ref<AnimationController> Create(const std::string& assignedName);

        int Advance(float deltaTime);
        void AddKeyFrame(std::string keyframeName);
        
        inline void SetBaseObjectName(std::string baseName) { m_BaseObjectName = baseName; }
        
        inline float GetAdvancedTime() { return m_AdvanceTimer - static_cast<int>(m_AdvanceTimer); }
        inline std::string GetBase() { return m_BaseObjectName; }

        Ref<VertexBuffer> GetVertexBuffer1();
        Ref<VertexBuffer> GetVertexBuffer2();

        virtual ~AnimationController() = default;

    private:
        std::string m_BaseObjectName;
        Ref<VertexBuffer> m_VertexBuffer1;
        Ref<VertexBuffer> m_VertexBuffer2;
        std::vector<std::string> m_KeyFrames;
        float m_AdvanceTimer;
    };
}