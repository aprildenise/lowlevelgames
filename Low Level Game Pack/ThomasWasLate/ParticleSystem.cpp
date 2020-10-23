
#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

using namespace sf;
using namespace std;

void ParticleSystem::init(int numParticles)
{
	// Setup the vertices.
	m_Vertices.setPrimitiveType(Points);
	m_Vertices.resize(numParticles);

	// Populate the particles vector by adding Particles to it
	// with somewhat randomized directions.
	for (int i = 0; i < numParticles; i++)
	{
		srand(time(0) + i);
		float angle = (rand() % 360) * 3.14f / 180.f;
		float speed = (rand() % 600) + 600.f;

		Vector2f direction;
		direction = Vector2f(cos(angle) * speed,
			sin(angle) * speed);

		m_Particles.push_back(Particle(direction));

	}

}

void ParticleSystem::update(float dt)
{
	m_Duration -= dt;

	// Loop through the particles and the vertices to call each particle's
	// update. Update the vertices with the particles' new positions as well.
	vector<Particle>::iterator i;
	int currentVertex = 0;
	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		(*i).update(dt); // Move the particle
		m_Vertices[currentVertex].position = (*i).getPosition(); // Update the vertex array
		currentVertex++;
	}

	if (m_Duration < 0)
	{
		m_IsRunning = false;
	}

}

void ParticleSystem::emitParticles(Vector2f startPosition)
{
	m_IsRunning = true;
	m_Duration = 2;

	// Loop through the particles and vertices to set their beginning
	// color and velocity.
	vector<Particle>::iterator i;
	int currentVertex = 0;
	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		m_Vertices[currentVertex].color = Color::Yellow;
		(*i).setPosition(startPosition);
		currentVertex++;
	}

}

void ParticleSystem::draw(RenderTarget& target, RenderStates states) const
{
	// Draw the entire particle system using the vertices.
	target.draw(m_Vertices, states);
}

bool ParticleSystem::running()
{
	return m_IsRunning;
}