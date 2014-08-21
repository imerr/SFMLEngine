/* 
 * File:   Factory.hpp
 * Author: iMer
 *
 * Created on 19. August 2014, 18:40
 */

#ifndef FACTORY_HPP
#define	FACTORY_HPP
#include "Scene.hpp"
#include "SpriteNode.hpp"
#include <json/json.h>
#include <iostream>
#include <fstream>
namespace engine {

    class Factory {
    protected:
        static std::map<std::string, std::function<bool(Json::Value& root) >> m_types;
    public:
        static void RegisterType(std::string name, std::function<bool(Json::Value& root) > callback);
        static void RemoveType(std::string name);
        static bool LoadJson(std::string filename, Json::Value& root);
        template <class T, typename... args> static T* create(std::string config, args... params) {
            Json::Value root;
            if (!LoadJson(config, root)){
                return nullptr;
            }
            T* thing = new T(params...);
            if (thing->initialize(root)) {
                return thing;
            }
            delete thing;
            return nullptr;
        }
        
    private:
        Factory() {

        }

    };
}

#endif	/* FACTORY_HPP */

