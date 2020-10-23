#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
private:
	/// <summary>
	/// Position of the bullet.
	/// </summary>
	Vector2f m_Position;

	/// <summary>
	/// Shape of the bullet.
	/// </summary>
	RectangleShape m_BulletShape;

	/// <summary>
	/// is the bullet currently in the air?
	/// </summary>
	bool m_InFlight = false;

	float m_BulletSpeed = 1000;

	/// <summary>
	/// Horizontal change of the bullet.
	/// </summary>
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	/// <summary>
	/// X position of the target that this bullet is flying at.
	/// </summary>
	float m_XTarget;
	float m_YTarget;

	/// <summary>
	/// Maximum X bound for the bullet.
	/// </summary>
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

public:
	/// <summary>
	/// Constructor. Sets the size of the bullet.
	/// </summary>
	Bullet();

	/// <summary>
	/// Stop the bullet from moving.
	/// </summary>
	void stop();

	/// <summary>
	/// Returns boolean isInFlight.
	/// </summary>
	/// <returns></returns>
	bool isInFlight();

	/// <summary>
	/// Launch a new bullet.
	/// </summary>
	/// <param name="startX"></param>
	/// <param name="startY"></param>
	/// <param name="xTarget"></param>
	/// <param name="yTarget"></param>
	void shoot(float startX, float startY,
		float xTarget, float yTarget);

	/// <summary>
	/// Get the position of the bullet. Used to detect collision with the zombies.
	/// </summary>
	/// <returns></returns>
	FloatRect getPosition();

	RectangleShape getShape();

	/// <summary>
	/// Update the position of the bullet.
	/// </summary>
	/// <param name="elapsedTime">Delta time since update was called. Represents one frame.</param>
	void update(float elapsedTime);

};