/* 
 * File:   Node.cpp
 * Author: iMer
 * 
 * Created on 3. Juli 2014, 01:00
 */

#include "Node.hpp"
namespace engine {

    Node::Node() {
    }

    Node::Node(const Node& orig) {
        this->m_scene = orig.m_scene;
    }

    Node::~Node() {
    }

    void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the transform
        states.transform *= getTransform();
        OnDraw(target, states);
        for (auto it = m_children.begin(); it != m_children.end(); it++) {
            (*it)->OnDraw(target, states);
        }
        PostDraw(target, states);
    }

    void Node::AddNode(Node* node) {
        m_children.push_back(node);
        node->SetParent(this);
        node->SetScene(m_scene);
    }

    void Node::RemoveNode(Node* node) {
        m_children.remove(node);
    }

    void Node::SetScene(Scene* scene) {
        m_scene = scene;
        for (auto it = m_children.begin(); it != m_children.end(); it++) {
            (*it)->SetScene(scene);
        }
    }

    Scene* Node::GetScene() const {
        return m_scene;
    }

    void Node::SetParent(Node* parent) {
        m_parent = parent;
    }

    Node* Node::GetParent() const {
        return m_parent;
    }

    void Node::update(sf::Time delta) {
        OnUpdate(delta);
        for (auto it = m_children.begin(); it != m_children.end(); it++) {
            (*it)->OnUpdate(delta);
        }
    }

}

