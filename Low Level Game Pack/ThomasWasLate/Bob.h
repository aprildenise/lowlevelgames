#pragma once
#include "PlayerCharacter.h"

class Bob : public PlayableCharacter
{
public:
	/// <summary>
	/// Constructori for Bob. Sets Bob's texture and their jump duration.
	/// </summary>
	Bob();
	bool virtual handleInput();

};

