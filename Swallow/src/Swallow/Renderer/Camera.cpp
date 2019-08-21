#include "swpch.hpp"
#include "Camera.hpp"
#include "gtx/transform.hpp"

namespace Swallow {

	Camera::Camera(){

	}

	Camera::Camera(const Camera& cpy)
	{
		if (this != &cpy)
			*this = cpy;
	}

	Camera &Camera::operator=(const Camera& rhs)
	{
		if (this != &rhs)
			*this = rhs;
		return *this;
	}

	Camera::Camera(const glm::mat4 &projection)
		:m_Position({ 0, 0, 0 }), m_Rotation({0, 0, 0}), m_ProjectionMatrix(projection)
	{
		Recalculate();
	}

	void Camera::Recalculate()
	{
		glm::mat4 xRotation = glm::rotate(glm::mat4(1.0f), m_Rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 yRotation = glm::rotate(glm::mat4(1.0f), m_Rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 zRotation = glm::rotate(glm::mat4(1.0f), m_Rotation.z, glm::vec3(0, 0, 1));
		m_TranslationMatrix = glm::translate(glm::mat4(1.0f), m_Position);
		m_RotationMatrix = zRotation * yRotation * xRotation;
		m_TranslationMatrix = glm::inverse(m_TranslationMatrix);
		m_RotationMatrix = glm::inverse(m_RotationMatrix);
		m_ViewMatrix = m_RotationMatrix * m_TranslationMatrix;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
		:Camera(glm::ortho(left, right, top, bottom)) {}

	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, float n, float f)
		: Camera(glm::ortho(left, right, top, bottom, n, f)) {
		SW_CORE_TRACE("{}, {}, {}, {}", left, right, top, bottom);
	}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float top, float bottom)
	{
		Camera::SetProjectionMatrix(glm::ortho(left, right, top, bottom, -1.0f, 1.0f));
	}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float top, float bottom, float n, float f)
	{
		Camera::SetProjectionMatrix(glm::ortho(left, right, top, bottom, n, f));
	}

	PerspectiveCamera::PerspectiveCamera(float fov, float ar, float n, float f)
		:Camera(glm::perspective(fov, ar, n, f)) {}

	void PerspectiveCamera::SetProjectionMatrix(float fov, float ar, float n, float f)
	{
		Camera::SetProjectionMatrix(glm::perspective(fov, ar, n, f));
	}
}