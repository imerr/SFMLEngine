/* 
 * File:   Factory.cpp
 * Author: iMer
 * 
 * Created on 19. August 2014, 18:40
 */

#include "Factory.hpp"
namespace engine {
    std::map<std::string, std::function<Node*(Json::Value& root, Node* parent) >> Factory::m_types = {
        std::make_pair(std::string("node"), std::function < Node * (Json::Value& root, Node * parent) >(Factory::CreateChildNode<Node>)),
        std::make_pair(std::string("sprite"), std::function < Node * (Json::Value& root, Node * parent) >(Factory::CreateChildNode<SpriteNode>)),
        std::make_pair(std::string("light"), std::function < Node * (Json::Value& root, Node * parent) >(Factory::CreateChildNode<Light>))
    };

    void Factory::RegisterType(std::string name, std::function<Node*(Json::Value& root, Node* parent) > callback) {
        m_types.insert(std::make_pair(name, callback));
    }

    void Factory::RemoveType(std::string name) {
        m_types.erase(name);
    }

    bool Factory::LoadJson(std::string filename, Json::Value & root) {
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

    Node * Factory::CreateChild(Json::Value root, Node * parent) {
        Json::Value childData;
        if (root["childData"].isString()) {
            if (!LoadJson(root["childData"].asString(), childData)) {
                std::cerr << "Couldn't load childData from file" << std::endl;
                return nullptr;
            }
        } else {
            childData = root["childData"];
        }
        MergeJson(childData, root);
        std::string type = childData.get("type", "node").asString();
        auto it = m_types.find(type);
        if (it == m_types.end()) {
            std::cerr << "Type '" << type << "' was not registered. Cant load child." << std::endl;
            return nullptr;
        }
        Node* c = it->second(childData, parent);
        if (!c) {
            return nullptr;
        }
        return c;
    }

    void Factory::MergeJson(Json::Value& a, Json::Value& b) { // http://stackoverflow.com/a/23860017/1318435
        if (!a.isObject() || !b.isObject()) return;

        for (const auto& key : b.getMemberNames()) {
            if (a[key].isObject()) {
                MergeJson(a[key], b[key]);
            } else {
                a[key] = b[key];
            }
        }
    }
}

