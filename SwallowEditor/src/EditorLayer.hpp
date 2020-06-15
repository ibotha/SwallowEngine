#pragma once
#include <Swallow.hpp>

namespace Swallow {
	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer();

		bool OnWindowResize(WindowResizeEvent& e);

		virtual void OnEvent(Event& e) override;
		virtual void OnImGuiRender() override;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;

		void ViewportWindow(bool* open);
		void PropertiesWindow(bool* open);

	private:
		OrthographicCameraController m_Camera;

		glm::vec4 col = { 0.2f, 0.5f, 0.8f, 1.0f };
		Ref<Texture2D> texture;
		Ref<Texture2D> spriteSheet;
		Ref<SubTexture2D> subtex;
		Ref<Framebuffer> framebuffer;
		int limit = 3;
		bool m_ViewportEnabled = true, m_PropertiesEnabled = true;
	};
}