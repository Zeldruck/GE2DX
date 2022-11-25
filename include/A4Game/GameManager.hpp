#pragma once

enum class EWindowGameState
{
	Menu,
	Game,
	End
};

class GameManager
{
	public:
		GameManager();
		GameManager(const GameManager&) = delete;
		GameManager(GameManager&&) = delete;
		~GameManager();

		void SetGameState(EWindowGameState _newGameState);
		EWindowGameState& GetGameState();

		bool IsWindowOpen() const;
		void CloseWindow();

		[[nodiscard]] bool IsStateOpen() const;
		void CloseState();
		void OpenState();

		void ResetGamePart();

		GameManager& operator=(const GameManager&) = delete;
		GameManager& operator=(GameManager&&) = delete;

		static GameManager& Instance();

	public:
		int m_gameScore;
	
	private:
		EWindowGameState m_gameState;

		bool m_isWindowOpen;
		bool m_isStateOpen;

		static GameManager* s_instance;
};
