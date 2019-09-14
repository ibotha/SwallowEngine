#pragma once
#include <Swallow.hpp>
#include "Layer2D.hpp"

class Sandbox : public Swallow::Application
{
public:
	Sandbox();
	virtual ~Sandbox();

private:
	Sandbox(const Sandbox &s) = default;
	Sandbox &operator=(const Sandbox &s) = default;

	Swallow::Ref<Layer2D> m_StartLayer;
};