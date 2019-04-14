#include <Swallow.h>

class StartLayer : public Swallow::Layer {
public:
	StartLayer() : Layer("Start Layer")
	{
	}

	void OnEvent(Swallow::Event &e) override {
		SW_TRACE("{0}", e);
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
		PushOverlay(new Swallow::ImGuiLayer());
	}

	~Sandbox() {

	}

private:

};


Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}