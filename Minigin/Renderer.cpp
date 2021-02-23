#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include <..\imgui-1.81\backends\imgui_impl_opengl2.h>
#include <..\imgui-1.81\backends\imgui_impl_sdl.h>


int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window * pWindow)
{
	m_ShowDemo = true;
	m_pWindow = pWindow;
	m_Renderer = SDL_CreateRenderer(pWindow, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	(pWindow, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
	ImGui_ImplSDL2_InitForOpenGL(pWindow, SDL_GL_GetCurrentContext());
}

void dae::Renderer::Render()
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();
	if (m_ShowDemo)
	{

		
		ImGui::SameLine(0);
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.f, 1.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(1.f, 1.f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(1.f, 1.f, 0.5f));
		ImGui::Button("Single Players");
		ImGui::PopStyleColor(3);
		ImGui::PopID();
		
		ImGui::SameLine(0);
		ImGui::PushID(1);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.75f, 1.f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.75f, 1.f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.75f, 1.f, 0.5f));
		ImGui::Button("Co-op");
		ImGui::PopStyleColor(3);
		ImGui::PopID();

		ImGui::SameLine(0);
		ImGui::PushID(2);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.25f, 1.f, 0.9f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.25f, 1.f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.25f, 1.f, 0.5f));
		ImGui::Button("Versus");
		ImGui::PopStyleColor(3);
		ImGui::PopID();
		//ImGui::ShowDemoWindow(&m_ShowDemo);
	}
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());


	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::ToggleDemo()
{
	m_ShowDemo = !m_ShowDemo;
}
