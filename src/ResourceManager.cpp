#include "ResourceManager.hpp"
#include "sdlpp_texture.hpp"
#include "sdlpp_renderer.hpp"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

std::shared_ptr<SDLpp_texture> ResourceManager::GetTexture(SDLpp_renderer& _renderer, const std::string& _path)
{
	std::map<std::string, std::shared_ptr<SDLpp_texture>>::iterator it;

	it = textures.find(_path);

	if (it != textures.end()) 
		// Found
	{
		std::shared_ptr<SDLpp_texture> texture = textures[_path];
		return texture;
	}
	else 
		// Not found
		// Need to load the texture
		// And to add it to the map
	{
		std::shared_ptr<SDLpp_texture> texture = std::make_shared<SDLpp_texture>(SDLpp_texture::LoadFromFile(_renderer, _path));
		textures[_path] = texture;

		return texture;
	}
}

void ResourceManager::Purge()
{
	std::map<std::string, std::shared_ptr<SDLpp_texture>>::iterator it;

	for (it = textures.begin(); it != textures.end(); ++it)
	{
		if (it->second.use_count() <= 0)
		{
			textures.erase(it->first);
			--it;
		}
	}
}
