#ifndef ENGINE_RESOURCEMANAGER_HPP
#define ENGINE_RESOURCEMANAGER_HPP

#include "util/singleton.hpp"
#include <map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <json/value.h>

namespace engine {

	class ResourceManager : public singleton<ResourceManager> {
	private:
		std::map<std::string, sf::Texture*> m_textures;
		std::map<std::string, sf::SoundBuffer*> m_soundBuffers;
		sf::Texture m_textureMissing;
	public:
		ResourceManager();
		virtual ~ResourceManager();

		sf::Texture* GetTexture(std::string path);

		sf::Sound* MakeSound(std::string path);
	};

}

#endif

