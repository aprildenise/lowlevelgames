#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
protected:
	Sprite m_Sprite;

	float m_JumpDuration;

	bool m_IsJumping;
	bool m_IsFalling;

	/// <summary>
	/// Did the player use the left key?
	/// </summary>
	bool m_LeftPressed;

	/// <summary>
	/// Did the player use the right key?
	/// </summary>
	bool m_RightPressed;

	/// <summary>
	/// Duration of the current jumping action.
	/// </summary>
	float m_TimeThisJump;

	/// <summary>
	/// Did the player just attempt to just?
	/// </summary>
	bool m_JustJumped = false;

private:


	Texture m_Texture;

	float m_Gravity;
	float m_Speed = 400;

	Vector2f m_Position;

	/// <summary>
	/// Rect representing the feet of this character.
	/// </summary>
	FloatRect m_Feet;

	/// <summary>
	/// Rect representing the head of this character.
	/// </summary>
	FloatRect m_Head;

	/// <summary>
	/// Rect representing the right side of this character.
	/// </summary>
	FloatRect m_Right;

	/// <summary>
	/// Rect representing the left side of this character.
	/// </summary>
	FloatRect m_Left;


public:

	/// <summary>
	/// Spawn the character at the given start position and with the given gravity.
	/// </summary>
	/// <param name="startPosition"></param>
	/// <param name="gravity"></param>
	void spawn(Vector2f startPosition, float gravity);


	/// <summary>
	/// Handle input from the player for this specific player character.
	/// </summary>
	/// <returns></returns>
	bool virtual handleInput() = 0;

	/// <summary>
	/// Get the position of the player based on the position of the sprite.
	/// </summary>
	/// <returns></returns>
	FloatRect getPosition();

	// Getters for this class' variables.
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();
	Sprite getSprite();

	/// <summary>
	/// Get the center of this character based on the sprite's global bounds.
	/// </summary>
	/// <returns></returns>
	Vector2f getCenter();
	
	/// <summary>
	/// Stop the player from falling by clamping their position to the ground.
	/// </summary>
	/// <param name="position"></param>
	void stopFalling(float position);
	/// <summary>
	/// Stop the player from moving right by clamping their position to the left.
	/// </summary>
	/// <param name="position"></param>
	void stopRight(float position);
	/// <summary>
	/// Stop the player from moving left by clamping their position to the right.
	/// </summary>
	/// <param name="position"></param>
	void stopLeft(float position);
	/// <summary>
	/// Stop a jump early by setting this player character's booleans.
	/// </summary>
	void stopJump();

	/// <summary>
	/// Update the physics of this character based in the player's input.
	/// </summary>
	/// <param name="elapsedTime"></param>
	void update(float elapsedTime);
};
