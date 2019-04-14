#include <Swallow.h>

class StartLayer : public Swallow::Layer {
public:
	StartLayer() : Layer("Start Layer")
	{
	}

	void OnEvent(Swallow::Event &e) override {
		SW_INFO("Start Layer received: {0}", e);
	}

	void OnUpdate() {
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