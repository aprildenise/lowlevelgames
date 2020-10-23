#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Particle
{
private:
	/// <summary>
	/// Position of the particle.
	/// </summary>
	Vector2f m_Position;

	/// <summary>
	/// Change of speed of this particle.
	/// </summary>
	Vector2f m_Velocity;

public:

	/// <summary>
	/// Constructor. Set the velocity of this particle based on the given direction.
	/// </summary>
	/// <param name="direction"></param>
	Particle(Vector2f direction);

	/// <summary>
	/// Move the particle using the velocity with the given time step.
	/// </summary>
	/// <param name="dt"></param>
	void update(float dt);

	// Setters for the variables.

	void setPosition(Vector2f position);

	// Getters for the variables.

	Vector2f getPosition();
};
