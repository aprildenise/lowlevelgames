#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;

	Vector2f m_Position;

	Sprite m_Sprite;
	Texture m_Texture;

	/// <summary>
	/// Screen resolution of the current game.
	/// </summary>
	Vector2f m_Resolution;

	/// <summary>
	/// Size of the current arena.
	/// </summary>
	IntRect m_Arena;

	/// <summary>
	/// Size of each tile in the arena.
	/// </summary>
	int m_TileSize;

	// Which directions is the player currently moving in
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	// How much health has the player got?
	int m_Health;
	// What is the maximum health the player can have
	int m_MaxHealth;

	// When was the player last hit
	Time m_LastHit;

	// Speed in pixels per second
	float m_Speed;


	// All our public functions will come next
public:

	Player();

	void spawn(IntRect arena, Vector2f resolution, int tileSize);
	void resetPlayerState();
	bool hit(Time timeHit);
	Time getLastHitTime();
	FloatRect getPosition();
	Vector2f getCenter();
	float getRotation();
	Sprite getSprite();
	int getHealth();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();
	void update(float elapsedTime, Vector2i mousePosition);
	void upgradeSpeed();
	void upgradeHealth();
	void increaseHealthLevel(int amount);
	void resetPlayerStats();


};



