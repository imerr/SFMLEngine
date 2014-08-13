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

namespace engine {

    SpriteNode::SpriteNode() : m_texture(0) {
    }

    SpriteNode::SpriteNode(const SpriteNode& orig) {
        m_texture = orig.m_texture;
        memcpy(m_vertices, orig.m_vertices, sizeof(m_vertices));
        m_textureRect = orig.m_textureRect;
    }

    SpriteNode::~SpriteNode() {
    }

    void SpriteNode::OnDraw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, 4, sf::TrianglesStrip, states);
    }

    void SpriteNode::UpdatePosition() {
        m_vertices[0].position = sf::Vector2f(0, 0);
        m_vertices[1].position = sf::Vector2f(0, m_textureRect.height);
        m_vertices[2].position = sf::Vector2f(m_textureRect.width, 0);
        m_vertices[3].position = sf::Vector2f(m_textureRect.width, m_textureRect.height);
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
        SetTexture(t, rect);
    }
    void SpriteNode::SetTexture(sf::Texture* texture, const sf::IntRect* rect){
        m_texture=texture;
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
        UpdatePosition();
        UpdateTexCoords();
    }
}
