#include "EditorApp.hpp"

namespace Swallow {

	Editor::Editor()
		:Application("Swallow Editor")
	{
		m_StartLayer = std::make_shared<EditorLayer>();
		PushLayer(m_StartLayer);
	}

	Editor::~Editor() {
	}

	Application* CreateApplication()
	{
		return (new Editor());
	}
}
