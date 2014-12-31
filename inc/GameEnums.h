#pragma once

namespace	Gomoku
{

	namespace GAME
	{
		enum Game
		{
			GOBAN,
			TITLE
		};
	}
	namespace	HUD
	{
		enum
		{
			SCORE,
			MAX
		};
	};

	namespace	Player
	{
		enum
		{
			// SHIP,
			// ENGINE_1,
			// ENGINE_2,
			// WEAPON_1,
			// WEAPON_2,
			MAX
		};
	};

	namespace	GameBackground
	{
		enum
		{
			DEFAULT,
			// REVERSED,
			MAX
		};
	};

	namespace	MainMenu
	{
		enum MODE
		{
			PLAYERPLAYER,
			PLAYERIA,
			EXIT,
			BACKGROUND,
			TITLE,
			MAX
		};
	};

	namespace	LobbyMenu
	{
		enum
		{
			BACKGROUND,
			TEXT,
			LOAD_ICON,
			MAX
		};
	};

	namespace	PauseMenu
	{
		enum
		{
			CONTINUE,
			EXIT,
			FILTER,
			MAX
		};
	};

	namespace	EndMenu
	{
		enum
		{
			RESULT,
			FILTER,
			SCORE,
			EXIT,
			MAX
		};
	}
}