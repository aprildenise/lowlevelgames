#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder
{
public:
	TextureHolder(); // Constructor
	static Texture& GetTexture(std::string const& filename);

private:
	std::map<std::string, sf::Texture> m_Textures;
	static TextureHolder* m_s_Instance; // Pointer used as the singleton
};

#endif