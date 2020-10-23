
#include "Engine.h"

using namespace sf;
using namespace std;

void Engine::populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel)
{
	vSoundEmitters.empty(); // Clear the vector.

	// Iterate through the array map in order to find the fire tiles,
	// which is where the emitters will be placed.
	// Keep track of the previous emitter placed so that we don't place
	// too many emitters in one area.
	FloatRect previousEmitter;
	for (int x = 0; x < (int)m_LM.getLevelSize().x; x++)
	{
		for (int y = 0; y < (int)m_LM.getLevelSize().y; y++)
		{
			// This tile is a fire tile.
			if (arrayLevel[y][x] == 2)
			{
				// Make sure that we're not placing an emitter too close to another one.
				if (!FloatRect(x * TILE_SIZE,
					y * TILE_SIZE,
					TILE_SIZE,
					TILE_SIZE).intersects(previousEmitter))
				{
					// Add the coordinates of this tile.
					vSoundEmitters.push_back(
						Vector2f(x * TILE_SIZE, y * TILE_SIZE));

					// Mark this as the previous emitter, with a little more height and width.
					previousEmitter.left = x * TILE_SIZE;
					previousEmitter.top = y * TILE_SIZE;
					previousEmitter.width = TILE_SIZE * 6;
					previousEmitter.height = TILE_SIZE * 6;
				}

			}

		}

	}
	return;

}