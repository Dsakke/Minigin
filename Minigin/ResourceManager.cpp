#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<dae::Texture2D> dae::ResourceManager::LoadTexture(const std::string& file) const
{
	auto it{ m_Textures.find(file) };
	if (it != m_Textures.end())
	{
		return it->second;
	}
	const auto fullPath = m_DataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	auto it{ m_Fonts.find(file) };
	if (it != m_Fonts.end())
	{
		return it->second;
	}
	return std::make_shared<Font>(m_DataPath + file, size);
}
