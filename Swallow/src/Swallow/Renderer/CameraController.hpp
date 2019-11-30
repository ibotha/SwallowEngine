#pragma once
#include <Swallow/Renderer/Camera.hpp>
#include <Swallow/Events/ApplicationEvent.hpp>
#include <Swallow/Events/MouseEvent.hpp>
#include <Swallow/Core/Timestep.hpp>

namespace Swallow {
	class CameraController
	{
	public:
		virtual ~CameraController() {}
		virtual const Camera &GetCamera() const = 0;
		virtual Camera &GetCamera() = 0;
		virtual void OnEvent(Event &e) = 0;
		virtual void OnUpdate(Timestep &ts) = 0;
	};

	class OrthographicCameraController : public CameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotationEnabled = false);
		virtual ~OrthographicCameraController() {}
		virtual inline const Camera &GetCamera() const override { return m_Camera; }
		virtual inline Camera &GetCamera() override { return m_Camera; }
		virtual void OnEvent(Event &e) override;
		virtual void OnUpdate(Timestep &ts) override;

		inline void SetZoomLevel(float zoom) { m_ZoomLevel = zoom; }
		inline float GetZoomLevel() const { return m_ZoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent &e);
		bool OnWindowResize(WindowResizeEvent &e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel;
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		bool m_RotationEnabled;
		OrthographicCamera m_Camera;
	};

	class PerspectiveCameraController : public CameraController
	{
	public:
		virtual ~PerspectiveCameraController() {}
		virtual inline const Camera &GetCamera() const override { return m_Camera; }
		virtual inline Camera &GetCamera() override { return m_Camera; }
		virtual void OnEvent(Event &e) override;
		virtual void OnUpdate(Timestep &ts) override;
	private:
		PerspectiveCamera m_Camera;
	};
}