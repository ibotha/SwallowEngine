#include "swpch.hpp"
#include "Transform.hpp"
#include "gtx/transform.hpp"

namespace Swallow {

    Transform::Transform()
	{
		this->m_Position = glm::vec3(0, 0, 0);
        this->m_Rotation = glm::vec3(0, 0, 0);
		this->m_Scale = glm::vec3(1, 1, 1);
		Recalculate();
	}

    Transform::Transform(glm::vec3 position, glm::vec3 rotation)
    {
        this->m_Position = position;
        this->m_Rotation = rotation;
		this->m_Scale = glm::vec3(1, 1, 1);
		Recalculate();
    }

    Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    {
        this->m_Position = position;
        this->m_Rotation = rotation;
		this->m_Scale = scale;
		Recalculate();
    }

    void Transform::Recalculate()
	{
		glm::mat4 xRotation = glm::rotate(m_Rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 yRotation = glm::rotate(m_Rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 zRotation = glm::rotate(m_Rotation.z, glm::vec3(0, 0, 1));

		m_TranslationMatrix = glm::translate(m_Position);
		m_RotationMatrix = zRotation * yRotation * xRotation;
		m_ScaleMatrix = glm::scale(m_Scale);

		m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
	}
}