#pragma once
#include <Swallow.hpp>

class Layer2D : public Swallow::Layer {
public:
	Layer2D();
	virtual ~Layer2D() = default;

	bool OnWindowResize(Swallow::WindowResizeEvent &e);

	virtual void OnEvent(Swallow::Event &e) override;
	virtual void OnImGuiRender() override;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Swallow::Timestep ts) override;

private:
	Swallow::OrthographicCameraController m_Camera;

	// Temp
	Swallow::Ref<Swallow::VertexArray> m_SquareVA;
	Swallow::Ref<Swallow::Shader> m_Shader;

	glm::vec4 col = { 0.2f, 0.5f, 0.8f, 1.0f };
};