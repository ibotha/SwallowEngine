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

        int Advance(float deltaTime);
        static Ref<AnimationController> Create(const std::string& assignedName);
        void AddKeyFrame(std::string keyframe_Name);
        //std::pair<Ref<VertexBuffer>, Ref<VertexBuffer>> GetBuffers();
        inline void SetBase(std::string baseName) { base = baseName; }
        inline void SetTimeAdvancer(float timeAdvancer) { m_timeAdvancer = timeAdvancer; }
        
        inline float GetAdvancedTime() { return m_advanceTimer - static_cast<int>(m_advanceTimer); }
        inline float GetTimeAdvancer() { return m_timeAdvancer - static_cast<int>(m_timeAdvancer); }
        inline std::string GetBase() { return base; }
        Ref<VertexBuffer> &GetVB1();
        Ref<VertexBuffer> &GetVB2();
        //inline void SetTransform(Ref<Transform> transform) { m_Transform = transform; }
        //inline void SetVertexArray(Ref<VertexArray> VA) { m_VertexArray = VA; }
        //inline void SetMaterial(Ref<MaterialInstance> material) { m_Material = material; }

		//inline Ref<Transform> GetTransform() { return m_Transform; }
		//inline Ref<VertexArray> GetVertexArray() { return m_VertexArray; }
        //inline Ref<MaterialInstance> GetMaterial() { return m_Material; }

        virtual ~AnimationController() = default;
        
        //void SetMaterial(Ref<Material> &material);

    private:
        std::string base;
        void ResetAnimationLoop();
        void UpdateNextKeyframe();
        Ref<VertexBuffer> vertexBuffer1;
        Ref<VertexBuffer> vertexBuffer2;
        std::vector<std::string> keyFrames;
        float m_advanceTimer;
        float m_timeAdvancer;
        int state;
    };
}