
#include "Engine.h"

void Engine::loadLevel()
{
	m_Playing = false; // Prevent updates.

	// Delete the previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];
	}
	delete[] m_ArrayLevel;

	// Load the next 2d array with the map for the level
	// And place the characters.
	m_ArrayLevel = m_LM.nextLevel(m_VALevel); // Level layout.
	populateEmitters(m_FireEmitters, m_ArrayLevel); // Sound.
	m_TimeRemaining = m_LM.getTimeLimit(); // Time.
	m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY); // Characters.
	m_Bob.spawn(m_LM.getStartPosition(), GRAVITY);

	// Done!
	m_NewLevelRequired = false;
}