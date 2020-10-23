
#include "zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

/// <summary>
/// Spawn a zombie within the given position, type, and randomizer seed.
/// </summary>
/// <param name="startX"></param>
/// <param name="startY"></param>
/// <param name="type"></param>
/// <param name="seed"></param>
void Zombie::spawn(float startX, float startY, int type, int seed)
{
	// Init sprites, speed, and health based on the given zombie type.
	switch (type)
	{
	case 0:
		// Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/bloater.png"));

		m_Speed = BLOATER_SPEED;
		m_Health = BLOATER_HEALTH;
		break;

	case 1:
		// Chaser
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/chaser.png"));

		m_Speed = CHASER_SPEED;
		m_Health = CHASER_HEALTH;
		break;

	case 2:
		// Crawler
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/crawler.png"));

		m_Speed = CRAWLER_SPEED;
		m_Health = CRAWLER_HEALTH;
		break;
	}

	// Modify the speed using the modifiers.
	srand((int)time(0) * seed);
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET; // Somewhere between 80 and 100
	modifier /= 100;
	m_Speed *= modifier; // Apply the modifier.

	// Set the position and origin.
	m_Position.x = startX;
	m_Position.y = startY;
	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}

/// <summary>
/// Damage the zombie.
/// </summary>
/// <returns>False if the zombie still has health, true if it hits 0 or lower.</returns>
bool Zombie::hit()
{
	// Decrease the zombie's health.
	m_Health--;
	if (m_Health < 0)
	{
		// Zombie has died.
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(
			"graphics/blood.png"));

		return true;
	}
	return false;
}


bool Zombie::isAlive()
{
	return m_Alive;
}

/// <summary>
/// Get the position of the zombie based in the global bounds of its sprite.
/// </summary>
/// <returns></returns>
FloatRect Zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}


Sprite Zombie::getSprite()
{
	return m_Sprite;
}

/// <summary>
/// Update the position and rotation of the zombie based on the player's position.
/// </summary>
/// <param name="elapsedTime">Delta time to modify the zombie's speed per frame.</param>
/// <param name="playerLocation"></param>
void Zombie::update(float elapsedTime,
	Vector2f playerLocation)
{

	// Update the zombie position variables so that it follows the player.
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;
	if (playerX > m_Position.x)
	{
		m_Position.x = m_Position.x +
			m_Speed * elapsedTime;
	}

	if (playerY > m_Position.y)
	{
		m_Position.y = m_Position.y +
			m_Speed * elapsedTime;
	}

	if (playerX < m_Position.x)
	{
		m_Position.x = m_Position.x -
			m_Speed * elapsedTime;
	}

	if (playerY < m_Position.y)
	{
		m_Position.y = m_Position.y -
			m_Speed * elapsedTime;
	}
	m_Sprite.setPosition(m_Position); // Move the sprite

	// Rotate the sprite so that it faces the direction it is moving towards.
	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x)
		* 180) / 3.141;
	m_Sprite.setRotation(angle);


}