/* 
 * File:   SpriteNode.cpp
 * Author: iMer
 * 
 * Created on 3. Juli 2014, 01:51
 */
#include <iostream>
#include <string.h>
#include "SpriteNode.hpp"
#include "ResourceManager.hpp"
#include "SFML/Graphics.hpp"
#include "Factory.hpp"

namespace engine {

    SpriteNode::SpriteNode(Scene* scene) : Node::Node(scene), m_texture(0) {
    }

    SpriteNode::~SpriteNode() {
    }

    void SpriteNode::OnDraw(sf::RenderTarget& target, sf::RenderStates states) {
        states.texture = m_texture;
        target.draw(m_vertices, 4, sf::TrianglesStrip, states);
    }

    void SpriteNode::UpdatePosition() {
        m_vertices[0].position = sf::Vector2f(0, 0);
        m_vertices[1].position = sf::Vector2f(0, m_size.y);
        m_vertices[2].position = sf::Vector2f(m_size.x, 0);
        m_vertices[3].position = sf::Vector2f(m_size.x, m_size.y);
    }

    void SpriteNode::UpdateTexCoords() {
        float left = static_cast<float> (m_textureRect.left);
        float right = left + m_textureRect.width;
        float top = static_cast<float> (m_textureRect.top);
        float bottom = top + m_textureRect.height;

        m_vertices[0].texCoords = sf::Vector2f(left, top);
        m_vertices[1].texCoords = sf::Vector2f(left, bottom);
        m_vertices[2].texCoords = sf::Vector2f(right, top);
        m_vertices[3].texCoords = sf::Vector2f(right, bottom);
    }

    void SpriteNode::SetTexture(std::string path, const sf::IntRect* rect) {
        sf::Texture* t = engine::ResourceManager::instance()->GetTexture(path);
        t->setRepeated(true);
        SetTexture(t, rect);
    }

    void SpriteNode::SetTexture(sf::Texture* texture, const sf::IntRect* rect) {
        m_texture = texture;
        if (rect) {
            m_textureRect.left = rect->left;
            m_textureRect.width = rect->width;
            m_textureRect.top = rect->top;
            m_textureRect.height = rect->height;
        } else {
            m_textureRect.left = 0;
            m_textureRect.width = m_texture->getSize().x;
            m_textureRect.top = 0;
            m_textureRect.height = m_texture->getSize().y;
        }
        if (!m_size.x && !m_size.y) {
            m_size.x = m_textureRect.width;
            m_size.y = m_textureRect.height;
        }
        UpdatePosition();
        UpdateTexCoords();
    }

    bool SpriteNode::initialize(Json::Value& root) {
        if (!Node::initialize(root)) {
            return false;
        }
        if (root.isMember("sprite")) {
            auto sprite = root["sprite"];
            if (sprite.isMember("texture")) {
                std::cout << "single texture" << std::endl;
                if (sprite.isMember("rect")) {
                    std::cout << "Rect" << std::endl;
                    sf::IntRect rect;
                    rect.left = sprite["rect"].get("left", 0).asInt();
                    rect.top = sprite["rect"].get("top", 0).asInt();
                    rect.width = sprite["rect"].get("width", 0).asInt();
                    rect.height = sprite["rect"].get("height", 0).asInt();
                    SetTexture(sprite["texture"].asString(), &rect);
                } else {
                    SetTexture(sprite["texture"].asString());
                }
            } else if (sprite.isMember("sheet")) {
                // TODO: Move this elsewhere&save?
                Json::Value sheet;
                if (Factory::LoadJson(sprite["sheet"].asString(), sheet)) {
                    auto tex = sheet["sprites"][sprite.get("index", 0).asInt()];
                    if (tex.empty() || tex.isNull()) {
                        std::cerr << "Empty/Nonexistant sprite index " << sprite.get("index", 0) << std::endl;
                    } else {
                        sf::IntRect rect;
                        rect.left = tex.get("left", 0).asInt();
                        rect.top = tex.get("top", 0).asInt();
                        rect.width = tex.get("width", 0).asInt();
                        rect.height = tex.get("height", 0).asInt();
                        SetTexture(sheet["texture"].asString(), &rect);
                    }
                } else {
                    std::cerr << "Loading spritesheet json failed." << std::endl;
                }
            }
        }
        return true;
    }

    uint8_t SpriteNode::GetType() const{
        return NT_SPRITE;
    }
}
