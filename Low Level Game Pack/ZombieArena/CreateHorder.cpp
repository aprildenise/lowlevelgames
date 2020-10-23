
#include "ZombieArena.h"
#include "Zombie.h"

/// <summary>
/// Spawn an array of zombies in a given area.
/// </summary>
/// <param name="numZombies"></param>
/// <param name="arena"></param>
/// <returns>An array of zombies made.</returns>
Zombie* createHorde(int numZombies, IntRect arena)
{
	Zombie* zombies = new Zombie[numZombies];

	// Find the bounds for the arena that the zombies will spawn into.
	int maxY = arena.height - 20;
	int minY = arena.top + 20;
	int maxX = arena.width - 20;
	int minX = arena.left + 20;

	// Iterate to fill the array.
	for (int i = 0; i < numZombies; i++)
	{

		// Choose a random place the zombie will spawn at.
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;
		switch (side)
		{
		case 0:
			// left
			x = minX;
			y = (rand() % maxY) + minY; // Generate a random Y coordinate.
			break;

		case 1:
			// right
			x = maxX;
			y = (rand() % maxY) + minY;
			break;

		case 2:
			// top
			x = (rand() % maxX) + minX; // Generate a random X coordinate.
			y = minY;
			break;

		case 3:
			// bottom
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		}

		// Choose what tyoe to generate.
		srand((int)time(0) * i * 2);
		int type = (rand() % 3);

		// Spawn the new zombie into the array
		zombies[i].spawn(x, y, type, i);

	}
	return zombies;
}