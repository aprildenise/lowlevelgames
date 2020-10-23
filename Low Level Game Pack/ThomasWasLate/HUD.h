#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
	Font m_Font;
	Text m_StartText;
	Text m_TimeText;
	Text m_LevelText;

public:
	/// <summary>
	/// Constructor. Init the HUD by seting up the text onto the screen.
	/// </summary>
	Hud();

	// Getters for the variables.
	Text getMessage();
	Text getLevel();
	Text getTime();

	// Setters for the variables.
	void setLevel(String text);
	void setTime(String text);
};