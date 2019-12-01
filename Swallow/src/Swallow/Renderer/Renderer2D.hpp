#pragma once

#include <Swallow/Renderer/Camera.hpp>

namespace Swallow
{

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primatives
	};

}