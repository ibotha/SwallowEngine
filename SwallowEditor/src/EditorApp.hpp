#pragma once
#include <Swallow.hpp>
#include "EditorLayer.hpp"

namespace Swallow {

	class Editor : public Application
	{
	public:
		Editor();
		virtual ~Editor();

	private:

		Ref<EditorLayer> m_StartLayer;
	};
}