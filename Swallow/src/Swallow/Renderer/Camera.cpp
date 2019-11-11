#include "swpch.hpp"
#include "gtx/transform.hpp"
#include "../AssetManager/Transform.hpp"
#include "Camera.hpp"
#include "Swallow/Application.hpp"

namespace Swallow {

	Camera::Camera(const glm::mat4 &projection)
		:m_ProjectionMatrix(projection), m_Position({ 0, 0, 0 }), m_Rotation({0, 0, 0})
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

	glm::vec2 Camera::WorldToScreenPoint(const glm::vec3 &point)
	{
		glm::vec3 ndc = glm::vec4(point.x, point.y, point.z, 0) * GetViewProjectionMatrix();
		glm::vec2 ret;
		ret.x = Application::Get().GetWindow().GetWidth() * ((ndc.x + 1.0f) * 0.5f);
		ret.y = Application::Get().GetWindow().GetHeight() * ((2.0f - (1.0f + ndc.y)) * 0.5f);
		return ret;
	}
}

/*
namespace Swallow {

	Camera::Camera(const glm::mat4 &projection) : m_ProjectionMatrix(projection)
	{
		m_Transform.SetPosition({0, 0, 0});
		m_Transform.SetRotation({0, 0, 0});
		Recalculate();
	}

	void Camera::Recalculate()
	{
		m_Transform.Recalculate();
		m_ViewMatrix = m_Transform.GetRotationMatrix() * m_Transform.GetTranslationMatrix();
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
		:Camera(glm::ortho(left, right, top, bottom)) {}


	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float n, float f)
		: Camera(glm::ortho(left, right, bottom, top, n, f)) {
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
*/