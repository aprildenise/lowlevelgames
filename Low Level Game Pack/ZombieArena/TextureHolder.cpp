#include "TextureHolder.h"
#include <assert.h>

using namespace sf;
using namespace std;

#pragma region Singleton
// Get the instance from the class in order to set it.
TextureHolder* TextureHolder::m_s_Instance = nullptr;
TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}
#pragma endregion

/// <summary>
/// Get a texture from the TextureHolder's map.
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
	// Use the singleton instance pointer above to get the texture map.
	auto& m = m_s_Instance->m_Textures;

	// Find the given filename in the map.
	auto keyValuePair = m.find(filename);
	if (keyValuePair != m.end())
	{
		// Return the found texture.
		return keyValuePair->second;
	}
	else
	{
		// Create a new texture based on this filename and return it.
		auto& texture = m[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}