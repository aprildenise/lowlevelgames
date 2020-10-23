#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class LevelManager
{
private:
	/// <summary>
	/// Number of tiles vertically and horizontally to make the level.
	/// </summary>
	Vector2i m_LevelSize;

	/// <summary>
	/// Coordinates in the game world where the player characters will spawn.
	/// </summary>
	Vector2f m_StartPosition;

	/// <summary>
	/// Used to modify the time remaining in each level, wheever the player completes a level.
	/// </summary>
	float m_TimeModifier = 1;

	/// <summary>
	/// The original time limit, without the modifier.
	/// </summary>
	float m_BaseTimeLimit = 0;

	int m_CurrentLevel = 0;
	const int NUM_LEVELS = 4;

public:

	/// <summary>
	/// Size of the tiles in the tilemap.
	/// </summary>
	const int TILE_SIZE = 50;

	/// <summary>
	/// Verices for each tile.
	/// </summary>
	const int VERTS_IN_QUAD = 4;

	/// <summary>
	/// Layout of tiles for the next level to be loaded.
	/// </summary>
	/// <param name="rVaLevel"></param>
	/// <returns></returns>
	int** nextLevel(VertexArray& rVaLevel);

	// Getters for variables.

	Vector2i getLevelSize();
	int getCurrentLevel();

	/// <summary>
	/// Get the time limit for the level, which applies the time modifier.
	/// </summary>
	/// <returns></returns>
	float getTimeLimit();
	Vector2f getStartPosition();


};
