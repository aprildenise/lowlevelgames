#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"

using namespace sf;
using namespace std;

class ParticleSystem : public Drawable
{
private:

	/// <summary>
	/// Particles of this system.
	/// </summary>
	vector<Particle> m_Particles;

	/// <summary>
	/// Used to draw the particles using the data in the Particles.
	/// </summary>
	VertexArray m_Vertices;

	/// <summary>
	/// How long this particle system is running for.
	/// </summary>
	float m_Duration;
	bool m_IsRunning = false;


public:

	/// <summary>
	/// From the Drawable class. Draw the particle system.
	/// </summary>
	/// <param name="target"></param>
	/// <param name="states"></param>
	virtual void draw(RenderTarget& target, RenderStates states) const;

	/// <summary>
	/// Create particles in this system.
	/// </summary>
	/// <param name="count">Number of particles in this system.</param>
	void init(int count);

	/// <summary>
	/// Start the particle system.
	/// </summary>
	/// <param name="position"></param>
	void emitParticles(Vector2f position);

	/// <summary>
	/// Update the movement of each particle.
	/// </summary>
	/// <param name="elapsed"></param>
	void update(float elapsed);

	bool running();

};


