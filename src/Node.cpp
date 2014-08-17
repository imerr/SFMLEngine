/* 
 * File:   Node.cpp
 * Author: iMer
 * 
 * Created on 3. Juli 2014, 01:00
 */

#include "Node.hpp"
#include "util/math.hpp"
#include "Scene.hpp"
#include <iostream>
namespace engine {

    Node::Node() : m_scene(nullptr), m_parent(nullptr), m_body(nullptr) {
    }

    Node::~Node() {
    }

    void Node::draw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
        // apply the transform
        if (m_body) {
            UpdateTransform(delta);
        }
        states.transform *= getTransform();
        OnDraw(target, states);
        for (auto it = m_children.begin(); it != m_children.end(); it++) {
            (*it)->draw(target, states, delta);
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

    sf::Transform Node::GetGlobalTransform() {
        if (m_parent) {
            return m_parent->GetGlobalTransform() * getTransform();
        }
        return getTransform();
    }

    sf::Vector2f Node::GetGlobalPosition() {
        return GetGlobalTransform().transformPoint(0, 0);
    }

    void Node::update(sf::Time interval) {
        if (m_body) {
            UpdatePhysicsTransform();
        }
        OnUpdate(interval);
        for (auto it = m_children.begin(); it != m_children.end(); it++) {
            (*it)->update(interval);
        }
    }

    void Node::UpdatePhysicsTransform() {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_physicsTransform.rot = m_body->GetAngle()*180 / util::fPI;
        m_physicsTransform.rotVel = m_body->GetAngularVelocity()*180 / util::fPI;
        m_physicsTransform.pos = m_body->GetPosition();
        m_physicsTransform.pos *= m_scene->GetPixelMeterRatio();
        m_physicsTransform.vel = m_body->GetLinearVelocity();
        m_physicsTransform.vel *= m_scene->GetPixelMeterRatio();
    }

    void Node::UpdateTransform(float delta) {
        std::lock_guard<std::mutex> lg(m_mutex);
        setRotation(m_physicsTransform.rot + delta * m_physicsTransform.rotVel);
        setPosition(m_physicsTransform.pos.x + delta * m_physicsTransform.vel.x, m_physicsTransform.pos.y + delta * m_physicsTransform.vel.y);
    }
}

