
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{

	// Load in a new level if needed.
	if (m_NewLevelRequired)
	{
		loadLevel();
	}

	if (m_Playing)
	{
		// Update the characters.
		m_Thomas.update(dtAsSeconds);
		m_Bob.update(dtAsSeconds);

		// Detect collisions and see if characters have reached the goal tile.
		if (detectCollisions(m_Thomas) && detectCollisions(m_Bob))
		{
			// Prompt a new level to be made.
			m_NewLevelRequired = true;
			m_SM.playReachGoal();

		}
		else
		{
			// Run bob's collision detection
			detectCollisions(m_Bob);
		}

	}

	// Iterate through the sound emitters in the game to check if the player
	// is close to them. If the player is, then play that emitter.
	vector<Vector2f>::iterator it;
	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		// Get the location of the emitter and check for collisions.
		float posX = (*it).x;
		float posY = (*it).y;
		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		// Play the sound and pass in the location as well
		if (m_Thomas.getPosition().intersects(localRect))
		{
			m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
		}
	}


	// Allow Bob and Thomas to jump on eachother.
	if (m_Bob.getFeet().intersects(m_Thomas.getHead()))
	{
		m_Bob.stopFalling(m_Thomas.getHead().top);
	}
	else if (m_Thomas.getFeet().intersects(m_Bob.getHead()))
	{
		m_Thomas.stopFalling(m_Bob.getHead().top);
	}


	// Check if the player has run out of time in the game.
	m_TimeRemaining -= dtAsSeconds;
	if (m_TimeRemaining <= 0)
	{
		m_NewLevelRequired = true;
	}


	// Set the appropriate view around the appropriate character,
	// depending on what views are currently active.
	if (m_SplitScreen)
	{
		m_LeftView.setCenter(m_Thomas.getCenter());
		m_RightView.setCenter(m_Bob.getCenter());
	}
	else
	{
		if (m_Character1)
		{
			m_MainView.setCenter(m_Thomas.getCenter());
		}
		else
		{
			m_MainView.setCenter(m_Bob.getCenter());
		}
	}


	// Attempt to update the HUD.
	m_FramesSinceLastHUDUpdate++;
	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
	{
		// Update the time text
		stringstream ssTime;
		ssTime << (int)m_TimeRemaining;
		m_Hud.setTime(ssTime.str());

		// Update the level text
		stringstream ssLevel;
		ssLevel << "Level:" << m_LM.getCurrentLevel();
		m_Hud.setLevel(ssLevel.str());

		m_FramesSinceLastHUDUpdate = 0;
	}

	// Update the particles
	if (m_PS.running())
	{
		m_PS.update(dtAsSeconds);
	}

}