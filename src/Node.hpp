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
#include <json/json.h>

namespace engine {
    class Scene;
    class Factory;
    struct physicsTransform {
    public:
        b2Vec2 pos;
        b2Vec2 vel;
        float rot;
        float rotVel;

        physicsTransform() : pos(0, 0), vel(0, 0), rot(0), rotVel(0) {
        }
    };
    enum NodeType{
        NT_NONE,
        NT_SPRITE,
        NT_SCENE,
        NT_BUTTON,
        NT_PARTICLESYSTEM,
        NT_END
    };
    class Node : public sf::Transformable, public sf::NonCopyable {
    protected:
        // mutex for locking things accessed in the graphics and logic thread, mainly when copying over position info and such
        std::mutex m_mutex;
        std::list<Node*> m_children;
        Scene* m_scene;
        Node* m_parent;
        b2Body* m_body;
        b2Joint* m_parentJoint;
        physicsTransform m_physicsTransform;
        sf::Vector2f m_size;
        bool m_opaque;
        // Update and render it
        bool m_active;
    public:
        Node(Scene* scene);
        virtual ~Node();
        void AddNode(Node* node);
        void RemoveNode(Node* node);
        void SetScene(Scene* scene);
        Scene* GetScene() const;
        Node* GetParent() const;
        sf::Transform GetGlobalTransform();
        sf::Vector2f GetGlobalPosition();
        virtual void update(sf::Time interval);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states, float delta);
        virtual bool initialize(Json::Value& root);
        virtual uint8_t GetType() const;
        void SetOpaque(bool lightBlocker);
        bool IsOpaque() const;
        void SetPosition(float x, float y);
        b2Body* GetBody() const;
        b2Joint* GetParentJoint() const;
        void SetActive(bool active);
        bool IsActive() const;
        std::list<Node*>& GetChildren();
    protected:
        friend Factory;
        void SetParent(Node* parent);
    private:

        virtual void OnUpdate(sf::Time interval) {
        };

        virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
        }

        virtual void PostDraw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
        }
        void UpdatePhysicsTransform();
        void UpdateTransform(float delta);
    };

}

#endif	/* ENGINE_NODE_HPP */

