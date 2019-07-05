#include "swpch.h"
#include "Camera.h"

namespace Swallow {
	Camera::Camera(glm::vec3 const & rot, glm::vec3 const & pos)
		:m_Pos(pos), m_Rot(rot)
	{
		Calculate();
	}

	void Camera::SetPerspectiveProjection(float fov, float ar, float n, float f)
	{
		m_Projection = glm::perspective(fov, ar, n, f);
	}

	void Camera::SetOrthographicProjection(float left, float right, float top, float bottom, float n, float f)
	{
		m_Projection = glm::ortho(left, right, top, bottom, n, f);
	}

	void Camera::Calculate()
	{
		glm::mat4 xRotation = glm::rotate(m_Rot.x, glm::vec3({ 1, 0, 0 }));
		glm::mat4 yRotation = glm::rotate(m_Rot.y, glm::vec3({ 0, 1, 0 }));
		glm::mat4 zRotation = glm::rotate(m_Rot.z, glm::vec3({ 0, 0, 1 }));
		m_TranslationMatrix = glm::translate(-m_Pos);
		m_RotationMatrix = xRotation * yRotation * zRotation;
		m_View =  m_RotationMatrix * m_TranslationMatrix;
		m_CameraMatrix = m_Projection * m_View;
	}
}