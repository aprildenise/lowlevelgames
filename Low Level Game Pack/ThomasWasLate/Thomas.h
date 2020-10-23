#pragma once
#include "PlayerCharacter.h"

class Thomas : public PlayableCharacter
{
public:
	/// <summary>
	/// Constructor for Thomas. Sets their texture and jump duration.
	/// </summary>
	Thomas();
	bool virtual handleInput();

};
