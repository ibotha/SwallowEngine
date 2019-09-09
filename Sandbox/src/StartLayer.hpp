#pragma once

#include <Swallow.hpp>
#include "imgui.h"
#include "gtx/transform.hpp"
#include <gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.hpp"

class StartLayer : public Swallow::Layer {
private:

	Swallow::Ref<Swallow::VertexArray> m_SquareVA;
	Swallow::Ref<Swallow::Texture2D> m_CheckerBoardTexture;
	Swallow::ShaderLibrary m_SLib;

	float	m_Y = 0.0f;
	float	m_YVelocity = 0.0f;
	bool	m_CanJump = true;
	glm::vec4 pos;
	glm::vec4 rot;
	glm::vec4 col = {1, 1, 1, 1};


	Swallow::PerspectiveCamera m_Camera;
public:
	StartLayer();
	StartLayer(const StartLayer &s) = default;
	StartLayer &operator=(const StartLayer &s) = default;
	virtual ~StartLayer() = default;

	bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
	bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
	bool OnKeyPressed(Swallow::KeyPressedEvent &e);

	virtual void OnEvent(Swallow::Event &e) override;
	virtual void OnImGuiRender() override;
	virtual void OnUpdate(Swallow::Timestep ts) override;
};