#pragma once
#include <Swallow.hpp>

class Layer2D : public Swallow::Layer {
public:
	Layer2D();
	virtual ~Layer2D();

	bool OnWindowResize(Swallow::WindowResizeEvent &e);

	virtual void OnEvent(Swallow::Event &e) override;
	virtual void OnImGuiRender() override;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Swallow::Timestep ts) override;

private:
	Swallow::OrthographicCameraController m_Camera;

	glm::vec4 col = { 0.2f, 0.5f, 0.8f, 1.0f };
	Swallow::Ref<Swallow::Texture2D> texture;
	Swallow::Ref<Swallow::Texture2D> spriteSheet;
	Swallow::Ref<Swallow::SubTexture2D> subtex;
	Swallow::Ref<Swallow::Entity> e;
	int limit = 3;
};