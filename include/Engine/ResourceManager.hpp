#ifndef _RESOURCEMANAGER_HPP_
#define _RESOURCEMANAGER_HPP_

#include <Engine/Export.hpp>
#include <unordered_map> //< std::unordered_map est plus efficace que std::map pour une association clé/valeur
#include <string>
#include <memory>

class SDLpp_texture;
class SDLpp_renderer;

class GE2DX_ENGINE_API ResourceManager
{
public:
	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	~ResourceManager() = default;

	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	std::shared_ptr<SDLpp_texture> GetTexture(SDLpp_renderer&, const std::string&);
	void Purge();

private:
	std::shared_ptr<SDLpp_texture> m_missingTexture;
	std::unordered_map<std::string /*texturePath*/, std::shared_ptr<SDLpp_texture>> m_textures;

};

#endif // !_RESOURCEMANAGER_HPP_
