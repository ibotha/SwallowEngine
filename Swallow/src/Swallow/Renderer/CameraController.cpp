#include <swpch.hpp>
#include <Swallow/Renderer/CameraController.hpp>
#include <Swallow/Core/Core.hpp>
#include <Swallow/Core/Input.hpp>
#include <Swallow/Core/KeyCodes.hpp>

namespace Swallow {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotationEnabled)
		:m_RotationEnabled(rotationEnabled), m_Position(0.0f), m_Rotation(0.0f), m_AspectRatio(aspectRatio), m_ZoomLevel(1.0f), m_Camera(-m_ZoomLevel * m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel)
	{
	}

	void OrthographicCameraController::OnEvent(Event & e)
	{
		SW_PROFILE_FUNCTION();
		EventDispatcher d(e);
		d.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		d.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	void OrthographicCameraController::OnUpdate(Timestep & ts)
	{
		SW_PROFILE_FUNCTION();
		if (Input::IsKeyPressed(SW_KEY_W))
			m_Position.y += 1 * m_ZoomLevel * ts.GetSeconds();
		if (Input::IsKeyPressed(SW_KEY_S))
			m_Position.y -= 1 * m_ZoomLevel * ts.GetSeconds();
		if (Input::IsKeyPressed(SW_KEY_D))
			m_Position.x += 1 * m_ZoomLevel * ts.GetSeconds();
		if (Input::IsKeyPressed(SW_KEY_A))
			m_Position.x -= 1 * m_ZoomLevel * ts.GetSeconds();

		if (Input::IsKeyPressed(SW_KEY_Q) && m_RotationEnabled)
			m_Rotation.z += 1 * ts.GetSeconds();
		if (Input::IsKeyPressed(SW_KEY_E) && m_RotationEnabled)
			m_Rotation.z -= 1 * ts.GetSeconds();

		m_Camera.SetPosition(m_Position);
		m_Camera.SetRotation(m_Rotation);
		m_Camera.Recalculate();
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent & e)
	{
		SW_PROFILE_FUNCTION();
		m_ZoomLevel -= e.GetYOffset();
		m_ZoomLevel = glm::clamp(m_ZoomLevel, 1.0f, 10000.0f);
		m_Camera.SetProjectionMatrix(-m_ZoomLevel * m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel);
		m_Camera.Recalculate();
		return false;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent & e)
	{
		SW_PROFILE_FUNCTION();
		m_AspectRatio = e.GetWidth() / static_cast<float>(e.GetHeight());

		m_Camera.SetProjectionMatrix(-m_ZoomLevel * m_AspectRatio, m_ZoomLevel * m_AspectRatio, -m_ZoomLevel, m_ZoomLevel);
		m_Camera.Recalculate();
		return false;
	}

	void PerspectiveCameraController::OnEvent(Event & e)
	{
	}

	void PerspectiveCameraController::OnUpdate(Timestep & ts)
	{
	}
}