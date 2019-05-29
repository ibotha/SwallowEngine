#include <Swallow.h>
#include "imgui.h"

class StartLayer : public Swallow::Layer {
public:
	StartLayer() : Layer("Start Layer")
	{
	}

	void OnEvent(Swallow::Event &e) override {
	}

	virtual void OnImGuiRender() override {
	}

	void OnUpdate() {
		auto[x, y] = Swallow::Input::GetMousePosition();
		if (Swallow::Input::IsKeyPressed(SW_KEY_LEFT_CONTROL))
			SW_CORE_TRACE("{0}, {1}", x, y);
	}
};

class Sandbox : public Swallow::Application
{
public:
	Sandbox() {
		PushLayer(new StartLayer());
	}

	~Sandbox() {

	}

private:

};


Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}