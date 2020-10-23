
#include "TextureHolder.h"
#include <assert.h>

using namespace sf;
using namespace std;

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
	// Use the singleton.
	auto& m = m_s_Instance->m_Textures;
	auto keyValuePair = m.find(filename);

	// If this filename exists in the map, return the paired texture.
	// Else, create a new texture from this filename, add it to the map,
	// And return it.
	if (keyValuePair != m.end())
	{
		return keyValuePair->second;
	}
	else
	{
		auto& texture = m[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}