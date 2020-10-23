#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder
{
private:
	/// <summary>
	/// Map of string file directories to the textures loaded from those directory.
	/// </summary>
	std::map<std::string, sf::Texture> m_Textures;

	/// <summary>
	/// Pointer to this class. Used as a singleton.
	/// </summary>
	static TextureHolder* m_s_Instance;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	TextureHolder();

	/// <summary>
	/// Use the given filename to get a texture from the map.
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	static sf::Texture& GetTexture(std::string const& filename);

};

#endif