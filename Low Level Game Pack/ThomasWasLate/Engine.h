#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include "ParticleSystem.h"

using namespace sf;

class Engine
{
private:
	
#pragma region Fields.

	/// <summary>
	/// The one texture holder.
	/// </summary>
	TextureHolder th;
	ParticleSystem m_PS;
	SoundManager m_SM;

	// Tilemap
	/// <summary>
	/// Size of the tiles in the tilemap.
	/// </summary>
	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;
	Texture m_TextureTiles;

	// Physics.
	/// <summary>
	/// Force of gravity for all the players.
	/// </summary>
	const int GRAVITY = 300;

	// Views and windows.
	RenderWindow m_Window;
	/// <summary>
	/// Main view for the game.
	/// </summary>
	View m_MainView;
	View m_LeftView;
	View m_RightView;

	/// <summary>
	/// Main background view for the game.
	/// </summary>
	View m_BGMainView;
	View m_BGLeftView;
	View m_BGRightView;

	/// <summary>
	/// View for UI/HUD
	/// </summary>
	View m_HudView;

	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	Shader m_RippleShader; // Shader for the background.

	/// <summary>
	/// Is the player currently playing?
	/// </summary>
	bool m_Playing = false;

	/// <summary>
	/// Is Character 1 in focus, or character 2?
	/// </summary>
	bool m_Character1 = true;

	/// <summary>
	/// Is the game starting in split screen or full screen?
	/// </summary>
	bool m_SplitScreen = false;
	float m_TimeRemaining;
	Time m_GameTimeTotal;
	bool m_NewLevelRequired = true;

	// Characters.
	Thomas m_Thomas;
	Bob m_Bob;

	LevelManager m_LM;

	/// <summary>
	/// Vertex array to draw the level.
	/// </summary>
	VertexArray m_VALevel;

	/// <summary>
	/// Representation of the level's map as a 2D.
	/// </summary>
	int** m_ArrayLevel = NULL;

	/// <summary>
	/// Location of sound emitters in the game world.
	/// </summary>
	vector <Vector2f> m_FireEmitters;

	/// <summary>
	/// Hud for the game.
	/// </summary>
	Hud m_Hud;
	/// <summary>
	/// Frames pased since the last time the HUD was updated.
	/// </summary>
	int m_FramesSinceLastHUDUpdate = 0;
	/// <summary>
	/// Number of frames that should pass first before updating the HUD.
	/// </summary>
	int m_TargetFramesPerHUDUpdate = 500;

#pragma endregion

	/// <summary>
	/// Check for any input from the player and handle it.
	/// </summary>
	void input();

	/// <summary>
	/// Updates the game to handle conditions to make the game continue running.
	/// </summary>
	/// <param name="dtAsSeconds"></param>
	void update(float dtAsSeconds);

	/// <summary>
	/// Draw the sprites on the screen as well as the views.
	/// </summary>
	void draw();

	/// <summary>
	/// Load the next level.
	/// </summary>
	void loadLevel();

	/// <summary>
	/// Detect collisions for the player characters.
	/// </summary>
	/// <param name="character"></param>
	/// <returns>If the player has reached the goal.</returns>
	bool detectCollisions(PlayableCharacter& character);

	/// <summary>
	/// Place emitters into the world in order to hear sound, using the array map.
	/// </summary>
	/// <param name="vSoundEmitters"></param>
	/// <param name="arrayLevel"></param>
	void populateEmitters(vector <Vector2f>& vSoundEmitters,
		int** arrayLevel);

public:
	/// <summary>
	/// Constructor. Sets up the views and textures for the game.
	/// </summary>
	Engine();

	/// <summary>
	/// Calls input(), update(), and draw() to run the engine.
	/// </summary>
	void run();

};
