#include <A4Game/GameManager.hpp>
#include <stdexcept>

GameManager::GameManager():
m_gameScore(0),
m_gameState(EWindowGameState::Menu),
m_isWindowOpen(true),
m_isStateOpen(true)
{
	if (s_instance != nullptr)
		throw std::runtime_error("only one GameManager can be created");

	s_instance = this;
}

GameManager::~GameManager()
{
	s_instance = nullptr;
}

void GameManager::SetGameState(EWindowGameState _newGameState)
{
	m_gameState = _newGameState;
}

EWindowGameState& GameManager::GetGameState()
{
	return m_gameState;
}

bool GameManager::IsWindowOpen() const
{
	return m_isWindowOpen;
}

void GameManager::CloseWindow()
{
	m_isWindowOpen = false;
}

bool GameManager::IsStateOpen() const
{
	return m_isStateOpen;
}

void GameManager::CloseState()
{
	m_isStateOpen = false;
}

void GameManager::OpenState()
{
	m_isStateOpen = true;
}

void GameManager::ResetGamePart()
{
	m_gameScore = 0;
}

GameManager& GameManager::Instance()
{
	if (!s_instance)
		throw std::runtime_error("GameManager hasn't been instantied");

	return *s_instance;
}

GameManager* GameManager::s_instance = nullptr;