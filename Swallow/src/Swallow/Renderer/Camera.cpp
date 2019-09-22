#include "swpch.hpp"
#include "Camera.hpp"
#include "gtx/transform.hpp"

namespace Swallow {

	Camera::Camera(const glm::mat4 &projection)
		:m_ProjectionMatrix(projection)
	{
		Recalculate();
	}

	void Camera::Recalculate()
	{
		m_ViewMatrix = m_RotationMatrix * m_TranslationMatrix;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetRotation(const glm::vec3 & rotation)
	{
		glm::mat4 xRotation = glm::rotate(glm::mat4(1.0f), -rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 yRotation = glm::rotate(glm::mat4(1.0f), -rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 zRotation = glm::rotate(glm::mat4(1.0f), -rotation.z, glm::vec3(0, 0, 1));
		m_RotationMatrix = xRotation * yRotation * zRotation;
	}

	void Camera::SetPosition(const glm::vec3 & position)
	{
		m_TranslationMatrix = glm::translate(glm::mat4(1.0f), -position);
	}

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:Camera(glm::ortho(left, right, bottom, top)) {}

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float n, float f)
		: Camera(glm::ortho(left, right, bottom, top, n, f)) {
	}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top)
	{
		Camera::SetProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f));
	}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top, float n, float f)
	{
		Camera::SetProjectionMatrix(glm::ortho(left, right, bottom, top, n, f));
	}

	PerspectiveCamera::PerspectiveCamera(float fov, float ar, float n, float f)
		:Camera(glm::perspective(fov, ar, n, f)) {}

	void PerspectiveCamera::SetProjectionMatrix(float fov, float ar, float n, float f)
	{
		Camera::SetProjectionMatrix(glm::perspective(fov, ar, n, f));
	}
}