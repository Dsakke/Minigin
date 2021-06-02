#include "LevelSwitcher.h"
#include "SceneManager.h"

void LevelSwitcher::AddLevel(const std::string& name)
{
	m_Levels.push_back(name);
}

void LevelSwitcher::SetGameOver(const std::string& name)
{
	m_GameOverMenu = name;
}

void LevelSwitcher::SetStartMenu(const std::string& name)
{
	m_StartMenu = name;
}

void LevelSwitcher::LoadFirstLevel()
{
	m_LevelIndex = 0;
	dae::SceneManager::GetInstance().SetCurrentScene(m_Levels[0]);
}

void LevelSwitcher::LoadNextlevel()
{
	if (++m_LevelIndex > m_Levels.size())
	{
		LoadGameOver();
	}
	else
	{
		dae::SceneManager::GetInstance().SetCurrentScene(m_Levels[m_LevelIndex]);
	}
}

void LevelSwitcher::LoadGameOver()
{
	dae::SceneManager::GetInstance().SetCurrentScene(m_GameOverMenu);
}

void LevelSwitcher::LoadStartMenu()
{
	dae::SceneManager::GetInstance().SetCurrentScene(m_StartMenu);
}
