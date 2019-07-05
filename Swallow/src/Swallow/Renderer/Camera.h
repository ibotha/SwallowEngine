#pragma once

namespace Swallow {
	class Camera
	{
	public:

		Camera(glm::vec3 const & rot, glm::vec3 const & pos);

		void SetPerspectiveProjection(float fov, float ar, float n, float f);
		void Camera::SetOrthographicProjection(float left, float right, float top, float bottom, float n, float f);
		void Calculate();
		void SetRotation(glm::vec3 const &rot) { m_Rot = rot; }
		void SetPosition(glm::vec3 const &pos) { m_Pos = pos; }

		glm::vec3 const & GetRotation() { return m_Rot; }
		glm::vec3 const & GetPosition() { return m_Pos; }
		glm::mat4 const & GetRotationMatrix() { return m_RotationMatrix; }
		glm::mat4 const & GetTranslationMatrix() { return m_TranslationMatrix; }
		glm::mat4 const & GetView() { return m_View; }
		glm::mat4 const & GetProjection() { return m_Projection; }
		glm::mat4 const & GetCameraMatrix() { return m_CameraMatrix; }

		virtual ~Camera() {}

	private:
		glm::mat4 m_CameraMatrix;
		glm::mat4 m_Projection;
		glm::mat4 m_RotationMatrix;
		glm::mat4 m_TranslationMatrix;
		glm::mat4 m_View;
		glm::vec3 m_Pos;
		glm::vec3 m_Rot;
	};
}