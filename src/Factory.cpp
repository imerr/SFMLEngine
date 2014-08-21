/* 
 * File:   Factory.cpp
 * Author: iMer
 * 
 * Created on 19. August 2014, 18:40
 */

#include "Factory.hpp"
namespace engine {
    std::map<std::string, std::function<bool(Json::Value& root) >> Factory::m_types = {
        /* {std::string("node"), std::function(&Factory::createNode)},
         {std::string("scene"), std::function(&Factory::createScene)},
         {std::string("sprite"), std::function(&Factory::createSpriteNode)},*/
    };

    void Factory::RegisterType(std::string name, std::function<bool(Json::Value& root) > callback) {
        m_types.insert(std::make_pair(name, callback));
    }

    void Factory::RemoveType(std::string name) {
        m_types.erase(name);
    }

    bool Factory::LoadJson(std::string filename, Json::Value& root) {
        Json::Reader reader;
        std::ifstream jconfig;
        jconfig.open(filename);
        if (!jconfig.good()) {
            std::cerr << "Could not open config file: " << strerror(errno) << std::endl;
            return false;
        }
        if (!reader.parse(jconfig, root)) {
            std::cerr << "Couldn't parse config" << std::endl << reader.getFormattedErrorMessages() << std::endl;
            jconfig.seekg(0);
            std::cerr << jconfig.rdbuf() << std::endl;
            return false;
        }
        return true;
    }
}

