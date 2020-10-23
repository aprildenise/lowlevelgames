#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie
{
private:
	// Define the speeds of each zombie type.
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;


	// Define the health of each zombie type.
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;

	// Used to add variance to each zombie's speed.
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;

	Vector2f m_Position;
	Sprite m_Sprite;
	float m_Speed;
	float m_Health;
	bool m_Alive;

public:

	bool hit();
	bool isAlive();

	/// <summary>
	/// Spawn a zombie within the given position, type, and randomizer seed.
	/// </summary>
	/// <param name="startX"></param>
	/// <param name="startY"></param>
	/// <param name="type"></param>
	/// <param name="seed"></param>
	void spawn(float startX, float startY, int type, int seed);
	
	FloatRect getPosition();
	Sprite getSprite();
	void update(float elapsedTime, Vector2f playerLocation);
};


