#ifndef _RESOURCEMANAGER_HPP_
#define _RESOURCEMANAGER_HPP_

#include <map>
#include <string>
#include <memory>

class SDLpp_texture;
class SDLpp_renderer;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	std::shared_ptr<SDLpp_texture> GetTexture(SDLpp_renderer&, const std::string&);
	void Purge();

private:
	std::map<std::string, std::shared_ptr<SDLpp_texture>> textures;

};

#endif // !_RESOURCEMANAGER_HPP_
