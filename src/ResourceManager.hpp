/* 
 * File:   ResourceManager.hpp
 * Author: iMer
 *
 * Created on 3. Juli 2014, 14:47
 */

#ifndef RESOURCEMANAGER_HPP
#define	RESOURCEMANAGER_HPP
#include "util/singleton.hpp"
#include <map>
#include "SFML/Graphics/Texture.hpp"
namespace engine{

    class ResourceManager : public util::singleton<ResourceManager> {
    private:
        std::map<std::string, sf::Texture*> m_textures;
        sf::Texture m_textureMissing;
    public:
        ResourceManager();
        sf::Texture* GetTexture(std::string path);
    };
    
}

#endif	/* RESOURCEMANAGER_HPP */

