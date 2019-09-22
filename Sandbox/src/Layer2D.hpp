#pragma once
#include <Swallow.hpp>

class Layer2D : public Swallow::Layer {
private:

	Swallow::Ref<Swallow::VertexArray> m_SquareVA;
	Swallow::Ref<Swallow::Texture2D> m_CheckerBoardTexture;
	Swallow::ShaderLibrary m_SLib;

	glm::vec4 col;


	Swallow::OrthographicCameraController m_Camera;
public:
	Layer2D();
	virtual ~Layer2D() = default;

	bool OnWindowResize(Swallow::WindowResizeEvent &e);

	virtual void OnEvent(Swallow::Event &e) override;
	virtual void OnImGuiRender() override;
	virtual void OnUpdate(Swallow::Timestep ts) override;
};