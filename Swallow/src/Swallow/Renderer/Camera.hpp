#pragma once

namespace Swallow {

	class Camera
	{
	public:

		Camera() = default;
		Camera(const Camera&) = default;
		Camera &operator=(const Camera&) = default;
		Camera(const glm::mat4 &projection);

		void Recalculate();
		void SetRotation(const glm::vec3 &rotation);
		void SetPosition(const glm::vec3 &position);

		const glm::mat4 & GetRotationMatrix() const { return m_RotationMatrix; }
		const glm::mat4 & GetTranslationMatrix() const { return m_TranslationMatrix; }
		const glm::mat4 & GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4 & GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4 & GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		virtual ~Camera() = default;

	protected:
		virtual void SetProjectionMatrix(const glm::mat4 &projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }
	private:
		glm::mat4 m_ViewProjectionMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_RotationMatrix;
		glm::mat4 m_TranslationMatrix;
		glm::mat4 m_ViewMatrix;
	};

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		OrthographicCamera(float left, float right, float bottom, float top, float n, float f);

		void SetProjectionMatrix(float left, float right, float bottom, float top);
		void SetProjectionMatrix(float left, float right, float bottom, float top, float n, float f);
	};

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float ar, float n, float f);

		void SetProjectionMatrix(float fov, float ar, float n, float f);
	};
}