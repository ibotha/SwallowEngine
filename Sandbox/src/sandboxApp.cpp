#include "swpch.h"
#include <Swallow.h>

class Sandbox : public Swallow::Application
{
public:
	Sandbox();
	~Sandbox();

private:

};

Sandbox::Sandbox()
{
}

Sandbox::~Sandbox()
{
}


Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}