#pragma once
#include "Singleton.h"
#include <vector>
#include <string>

class LevelSwitcher : public dae::Singleton<LevelSwitcher>
{
public:
	void AddLevel(const std::string& name);
	void SetGameOver(const std::string& name);
	void SetStartMenu(const std::string& name);

	void LoadFirstLevel();
	void LoadNextlevel();
	void LoadGameOver();
	void LoadStartMenu();
private:
	friend class Singleton<LevelSwitcher>;

	std::vector<std::string> m_Levels;
	std::string m_GameOverMenu;
	std::string m_StartMenu;
	uint32_t m_LevelIndex;
	LevelSwitcher() = default;
};