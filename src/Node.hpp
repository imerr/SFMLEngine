/* 
 * File:   Node.hpp
 * Author: iMer
 *
 * Created on 3. Juli 2014, 01:00
 */

#ifndef ENGINE_NODE_HPP
#define	ENGINE_NODE_HPP
#include <list>
#include <mutex>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/System/Time.hpp"
#include "Box2D/Box2D.h"
namespace engine {
    class Scene;

    struct physicsTransform {
    public:
        b2Vec2 pos;
        b2Vec2 vel;
        float rot;
        float rotVel;

        physicsTransform() : pos(0, 0), vel(0, 0), rot(0), rotVel(0) {
        }
    };

    class Node : public sf::Transformable, public sf::NonCopyable {
    protected:
        // mutex for locking things accessed in the graphics and logic thread, mainly when copying over position info and such
        std::mutex m_mutex;
        std::list<Node*> m_children;
        Scene* m_scene;
        Node* m_parent;
        b2Body* m_body;
        physicsTransform m_physicsTransform;

    public:
        Node();
        virtual ~Node();
        void AddNode(Node* node);
        void RemoveNode(Node* node);
        void SetScene(Scene* scene);
        Scene* GetScene() const;
        Node* GetParent() const;
        virtual void update(sf::Time interval);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states, float delta);
    protected:
        void SetParent(Node* parent);
    private:

        virtual void OnUpdate(sf::Time interval) {
        };

        virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) {
        }

        virtual void PostDraw(sf::RenderTarget& target, sf::RenderStates states) {
        }
        void UpdatePhysicsTransform();
        void UpdateTransform(float delta);
    };

}

#endif	/* ENGINE_NODE_HPP */

