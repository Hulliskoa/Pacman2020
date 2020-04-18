#pragma once

/*! \brief
 *		Enum class for all possible game states in the game
 *
 *
 *
 */
enum class GameState {
	MAIN_MENU,
	GAME_RUNNING,
	GAME_RUNNING_FLEE,
	GAME_RUNNING_FLEE_ENDING,
	PACMAN_DIED,
	LEVEL_COMPLETE,
	GAME_STARTED,
	GAME_PAUSED,
	RESTART_LEVEL,
	EXIT_GAME,
	GAME_OVER
};