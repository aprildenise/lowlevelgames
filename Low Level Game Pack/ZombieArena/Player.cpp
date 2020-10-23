#include "player.h"
#include "TextureHolder.h"

Player::Player()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/player.png"));

	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	m_Sprite.setOrigin(25, 25);
}

// Player interactions.

/// <summary>
/// Spawn the player with the given arena, resolution, and tilesize
/// </summary>
/// <param name="arena"></param>
/// <param name="resolution"></param>
/// <param name="tileSize"></param>
void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	// Place the player in the middle of the arena
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 2;

	// Store the given dimensions and variables into the Player.
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	m_TileSize = tileSize;

	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;

}

/// <summary>
/// Reset the Player's speed, health, and max health.
/// </summary>
void Player::resetPlayerState() {
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

/// <summary>
/// Get the value in m_LastHit.
/// </summary>
/// <returns></returns>
Time Player::getLastHitTime()
{
	return m_LastHit;
}

/// <summary>
/// Attempt to damage the player. The player will loose health once it has passed
/// their iframes.
/// </summary>
/// <param name="timeHit">Time in which the player has been hit.</param>
/// <returns>True if the player is damaged. False elsewise.</returns>
bool Player::hit(Time timeHit)
{
	// Check if the player has bit hit in the last seconds.
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)// 2 tenths of second
	{
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else
	{
		return false;
	}

}

// Player getters.

/// <summary>
/// Get the position of the player based on the location of their Sprite.
/// </summary>
/// <returns></returns>
FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

/// <summary>
/// Get the center of the player based on the player's movement input.
/// </summary>
/// <returns></returns>
Vector2f Player::getCenter()
{
	return m_Position;
}

float Player::getRotation()
{
	return m_Sprite.getRotation();
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

int Player::getHealth()
{
	return m_Health;
}

// Player movement.

void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}

void Player::moveUp()
{
	m_UpPressed = true;
}

void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::stopUp()
{
	m_UpPressed = false;
}

void Player::stopDown()
{
	m_DownPressed = false;
}


/// <summary>
/// Update the player based on player input/movement.
/// </summary>
/// <param name="elapsedTime"></param>
/// <param name="mousePosition"></param>
void Player::update(float elapsedTime, Vector2i mousePosition)
{

	// Move the playe based on input.
	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}

	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	// Set the new position.
	m_Sprite.setPosition(m_Position);

	// Keep the player in the arena by checking if they have go outside its bounds.
	// If they've had, clamp their position to remain inside the arena.
	if (m_Position.x > m_Arena.width - m_TileSize)
	{
		m_Position.x = m_Arena.width - m_TileSize;
	}

	if (m_Position.x < m_Arena.left + m_TileSize)
	{
		m_Position.x = m_Arena.left + m_TileSize;
	}

	if (m_Position.y > m_Arena.height - m_TileSize)
	{
		m_Position.y = m_Arena.height - m_TileSize;
	}

	if (m_Position.y < m_Arena.top + m_TileSize)
	{
		m_Position.y = m_Arena.top + m_TileSize;
	}

	// Calculate the player rotation based on the mouse position.
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2,
		mousePosition.x - m_Resolution.x / 2)
		* 180) / 3.141;

	// Set the rotation.
	m_Sprite.setRotation(angle);
}

/// <summary>
/// Add more speed to the player.
/// </summary>
void Player::upgradeSpeed()
{
	// 20% speed upgrade
	m_Speed += (START_SPEED * .2);
}


/// <summary>
/// Add more health to the player.
/// </summary>
void Player::upgradeHealth()
{
	// 20% max health upgrade
	m_MaxHealth += (START_HEALTH * .2);

}

/// <summary>
/// Add more health to the player's health limit.
/// </summary>
/// <param name="amount"></param>
void Player::increaseHealthLevel(int amount)
{
	m_Health += amount;

	// But not beyond the maximum
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}

void Player::resetPlayerStats()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

