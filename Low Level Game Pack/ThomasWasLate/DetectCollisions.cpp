
#include "Engine.h"

bool Engine::detectCollisions(PlayableCharacter& character)
{
	bool reachedGoal = false;

	// Find the size of the character.
	FloatRect detectionZone = character.getPosition();

	// Make a FloatRect used to find collisions.
	FloatRect block;
	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	// Build a zone around the character and their current position to
	// check for collisions.
	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3;

	// Make sure we don't attempt to check for collisions that are in
	// negative positions or outside of the map array.
	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	if (endX >= m_LM.getLevelSize().x) endX = m_LM.getLevelSize().x;
	if (endY >= m_LM.getLevelSize().y) endY = m_LM.getLevelSize().y;

	// Check if the player has fallen out of the map.
	FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);
	if (!character.getPosition().intersects(level))
	{
		character.spawn(m_LM.getStartPosition(), GRAVITY); // Respawn the charcter.
	}

	// Loop through the tiles the character is colliding with.
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// Init the starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;

			// Check if the player is in water or lava to by checking the array map.
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				// If the player is intersecting one of these tiles.
				if (character.getHead().intersects(block))
				{
					character.spawn(m_LM.getStartPosition(), GRAVITY);
					if (m_ArrayLevel[y][x] == 2)// Fire, ouch!
					{
						// Play a sound
						m_SM.playFallInFire();
					}
					else // Water
					{
						// Play a sound
						m_SM.playFallInWater();
					}
				}
			}


			// If the character is not colliding with water or lava, they are
			// colliding with an ordinary block.
			if (m_ArrayLevel[y][x] == 1)
			{
				// Make sure the character stops at the block, even when they
				// attempt to move.
				if (character.getRight().intersects(block))
				{
					character.stopRight(block.left);
				}
				else if (character.getLeft().intersects(block))
				{
					character.stopLeft(block.left);
				}

				if (character.getFeet().intersects(block))
				{
					character.stopFalling(block.top);
				}
				else if (character.getHead().intersects(block))
				{
					character.stopJump();
				}
			}


			// Attempt to run the particle system if the player is colliding with
			// water or lava.
			if (!m_PS.running()) {
				if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
				{
					if (character.getFeet().intersects(block))
					{
						// Start the particle system.
						m_PS.emitParticles(character.getCenter());

					}
				}
			}


			// Check if the player has reached the goal.
			if (m_ArrayLevel[y][x] == 4)
			{
				reachedGoal = true;
			}

		}

	}

	// All done, return, wheteher or not a new level might be required
	return reachedGoal;
}