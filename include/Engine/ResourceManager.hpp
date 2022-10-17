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
	ResourceManager(SDLpp_renderer& renderer);
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	~ResourceManager();

	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	static ResourceManager& Instance();

	void Clear();

	const std::shared_ptr<SDLpp_texture>& GetTexture(const std::string& texturePath);

	void Purge();

private:
	std::shared_ptr<SDLpp_texture> m_missingTexture;
	std::unordered_map<std::string /*texturePath*/, std::shared_ptr<SDLpp_texture>> m_textures;

	SDLpp_renderer& m_renderer;

	static ResourceManager* s_instance;

};

#endif // !_RESOURCEMANAGER_HPP_
