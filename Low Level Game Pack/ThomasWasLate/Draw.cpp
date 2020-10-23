
#include "Engine.h"

void Engine::draw()
{

	m_Window.clear(Color::White);

	// Update the shader parameters
	m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds());


	if (!m_SplitScreen)
	{
		// Switch views to show the main views.
		// Draw the background main view first, and then the rest.
		m_Window.setView(m_BGMainView); 
		//m_Window.draw(m_BackgroundSprite); 
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);
		m_Window.setView(m_MainView);

		// Draw the level.
		m_Window.draw(m_VALevel, &m_TextureTiles);

		// Draw the characters.
		m_Window.draw(m_Thomas.getSprite());
		m_Window.draw(m_Bob.getSprite());

		// Draw the particle system
		if (m_PS.running())
		{
			m_Window.draw(m_PS);
		}
	}
	else
	{
		// Switch views to show the split screen view.
		// Remember to draw the background first.

		// First draw Thomas' side of the screen, the left.
		m_Window.setView(m_BGLeftView);
		//m_Window.draw(m_BackgroundSprite);
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);
		m_Window.setView(m_LeftView);
		// Draw the level.
		m_Window.draw(m_VALevel, &m_TextureTiles);
		// Draw the characters.
		m_Window.draw(m_Bob.getSprite());
		m_Window.draw(m_Thomas.getSprite());
		// Draw the particle system
		if (m_PS.running())
		{
			m_Window.draw(m_PS);
		}

		// Now draw Bob's side of the screen, the right.
		m_Window.setView(m_BGRightView);
		//m_Window.draw(m_BackgroundSprite);
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);
		m_Window.setView(m_RightView);
		// Draw the level again.
		m_Window.draw(m_VALevel, &m_TextureTiles);
		// Draw the characters again.
		m_Window.draw(m_Bob.getSprite());
		m_Window.draw(m_Thomas.getSprite());
		// Draw the particle system
		if (m_PS.running())
		{
			m_Window.draw(m_PS);
		}

	}

	// Switch to the HUD view to draw it.
	m_Window.setView(m_HudView);
	m_Window.draw(m_Hud.getLevel());
	m_Window.draw(m_Hud.getTime());
	if (!m_Playing)
	{
		m_Window.draw(m_Hud.getMessage());
	}


	// Display it all.
	m_Window.display();
}