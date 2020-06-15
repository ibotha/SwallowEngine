#include "EditorLayer.hpp"
#include "gtx/transform.hpp"
#include <gtc/type_ptr.hpp>
#include <imgui.h>

namespace Swallow {
#define AR (Application::Get().GetWindow().GetWidth() / static_cast<float>(Application::Get().GetWindow().GetHeight()))

	EditorLayer::EditorLayer()
		:Layer("Sandbox2D"), m_Camera(AR)
	{
	}

	EditorLayer::~EditorLayer()
	{
	}

	bool EditorLayer::OnWindowResize(WindowResizeEvent& e)
	{
		FramebufferSpecification spec;
		spec.Width = Application::Get().GetWindow().GetWidth();
		spec.Height = Application::Get().GetWindow().GetHeight();

		framebuffer = Framebuffer::Create(spec);
		return false;
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_Camera.OnEvent(e);
		EventDispatcher d(e);
		d.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(EditorLayer::OnWindowResize));
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool p_open = true;
		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool opt_fullscreen = opt_fullscreen_persistant;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit", NULL, false))
					Application::Get().End();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("scene", NULL, false))
					m_ViewportEnabled = true;
				if (ImGui::MenuItem("properties", NULL, false))
					m_PropertiesEnabled = true;
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		if (m_ViewportEnabled)
			ViewportWindow(&m_ViewportEnabled);
		if (m_PropertiesEnabled)
			PropertiesWindow(&m_PropertiesEnabled);

		ImGui::End();
	}

	void EditorLayer::ViewportWindow(bool* open)
	{
		ImVec2 hold = ImGui::GetStyle().WindowPadding;
		ImGui::GetStyle().WindowPadding = { 0,0 };
		static ImVec2 dim = {0, 0};
		if ((dim.y * (AR)) < dim.x)
		{
			float newx = dim.y * (float)(AR);
			ImGui::GetStyle().WindowPadding.x = (dim.x - newx) / 2;
			dim.x = newx;
		}
		else
		{
			float newy = dim.x / (float)(AR);
			ImGui::GetStyle().WindowPadding.y = (dim.y - newy) / 2;
			dim.y = newy;
		}
		ImGui::Begin("Scene", open, ImGuiWindowFlags_NoScrollbar);
		RendererID image = framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)image, dim, { 0, 1 }, { 1, 0 });
		dim = ImGui::GetWindowSize();
		dim.y -= ImGui::GetTextLineHeight() + ImGui::GetStyle().FramePadding.y + ImGui::GetStyle().ItemSpacing.y;
		ImGui::End();

		ImGui::GetStyle().WindowPadding = hold;
	}

	void EditorLayer::PropertiesWindow(bool* open)
	{
		ImGui::Begin("Properties", open);
		ImGui::Text("No object selected!");
		ImGui::End();
	}

	void EditorLayer::OnAttach()
	{
		texture = Texture2D::Create("assets/textures/CheckerBoard.png");
		spriteSheet = Texture2D::Create("assets/textures/sprite_sheet.png");
		subtex = SubTexture2D::CreateFromTilePallet(spriteSheet, { 1,3 }, { 1,1 }, { 16, 16 }, { 1, 1 });

		FramebufferSpecification spec;
		spec.Width = Application::Get().GetWindow().GetWidth();
		spec.Height = Application::Get().GetWindow().GetHeight();

		framebuffer = Framebuffer::Create(spec);
	}

	void EditorLayer::OnDetach()
	{
		texture.reset();
		spriteSheet.reset();
		subtex.reset();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		SW_PROFILE_FUNCTION();
		{
			SW_PROFILE_SCOPE("CameraController::OnUpdate");
			m_Camera.OnUpdate(ts);
		}

		{
			SW_PROFILE_SCOPE("RenderPrep");
			framebuffer->Bind();
			RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			RenderCommand::Clear();
		}

		{
			SW_PROFILE_SCOPE("RenderDraw");

			Renderer2D::ResetStatistics();
			Renderer2D::BeginScene(m_Camera.GetCamera());

			static float rot = 0.0f;

			//for (int x = 0; x < limit; x++)
			//	for (int y = 0; y < limit; y++)
			//		Renderer2D::DrawQuad({ x + 6.0f, y + 6.0f }, { 0.9f, 0.9f }, { 1, 1.0f - (float)y / (float)limit, 1.0f - (float)x / (float)limit, 1.0f });
			//Renderer2D::DrawQuad({ 0.0f, 1.6f }, { 0.5f, 0.5f }, { 0.0f, 8.0f, 6.0f, 1.0f });
			//Renderer2D::DrawQuad({ 0.5f, 0 }, { 1.0f, 2.0f }, col, rot += 0.1f * ts.GetSeconds());
			//Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, texture, 0.0f, 10.0f);
			Renderer2D::DrawQuad({ -5.0f, -10.0f, 0.1f }, { 10.0f, 10.0f }, subtex);

			Renderer2D::EndScene();
			framebuffer->Unbind();
		}
	}
}
