#pragma once
#include <SFML/Audio.hpp>

using namespace sf;

class SoundManager
{
private:
	// The buffers for each sound.
	SoundBuffer m_FireBuffer;
	SoundBuffer m_FallInFireBuffer;
	SoundBuffer m_FallInWaterBuffer;
	SoundBuffer m_JumpBuffer;
	SoundBuffer m_ReachGoalBuffer;

	// All the sounds to be used.
	Sound m_Fire1Sound;
	Sound m_Fire2Sound;
	Sound m_Fire3Sound;
	Sound m_FallInFireSound;
	Sound m_FallInWaterSound;
	Sound m_JumpSound;
	Sound m_ReachGoalSound;

	// Choose the next FireSound to play.
	int m_NextSound = 1;

public:
	/// <summary>
	/// Constructor. Setups all the buffers and sounds, along with the buffer settings
	/// like accentuation and loop.
	/// </summary>
	SoundManager();

	/// <summary>
	/// Play one of the fire sounds based on where the sound is emitting from and
	/// where the player is.
	/// </summary>
	/// <param name="emitterLocation"></param>
	/// <param name="listenerLocation"></param>
	void playFire(Vector2f emitterLocation, Vector2f listenerLocation);

	// Play the others sounds.
	void playFallInFire();
	void playFallInWater();
	void playJump();
	void playReachGoal();
};

