#pragma once

namespace Swallow {

    class Transform
    {
    public:
        Transform();
        Transform(glm::vec3 position, glm::vec3 rotation);
        Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
        Transform &operator=(const Transform&) = default;
        Transform(const Transform&) = default;

        void Recalculate();
        inline void SetPosition(const glm::vec3 &position) { m_Position = position; }
        inline void SetRotation(const glm::vec3 &rotation) { m_Rotation = rotation; }
        inline void SetScale(const glm::vec3 &scale) { m_Scale = scale; }

		inline const glm::vec3 & GetRotation() const { return m_Rotation; }
		inline const glm::vec3 & GetPosition() const { return m_Position; }
		inline const glm::vec3 & GetScale() const { return m_Scale; }
        inline const glm::mat4 & GetRotationMatrix() const { return m_RotationMatrix; }
		inline const glm::mat4 & GetTranslationMatrix() const { return m_TranslationMatrix; }
		inline const glm::mat4 & GetScaleMatrix() const { return m_ScaleMatrix; }
        inline const glm::mat4 & GetModelMatrix() const { return m_ModelMatrix; }
        
        virtual ~Transform() = default;

    private:
		glm::mat4 m_RotationMatrix;
        glm::mat4 m_ScaleMatrix;
		glm::mat4 m_TranslationMatrix;
        glm::mat4 m_ModelMatrix;
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
        glm::vec3 m_Scale;
    };
}