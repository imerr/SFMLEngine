/* 
 * File:   Node.hpp
 * Author: iMer
 *
 * Created on 3. Juli 2014, 01:00
 */

#ifndef ENGINE_NODE_HPP
#define	ENGINE_NODE_HPP
#include <list>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/System/Time.hpp"
namespace engine {
    class Scene;
    class Node : public sf::Drawable, public sf::Transformable {
    protected:
        std::list<Node*> m_children;
        Scene* m_scene;
        Node* m_parent;
    public:
        Node();
        Node(const Node& orig);
        virtual ~Node();
        void AddNode(Node* node);
        void RemoveNode(Node* node);
        void SetScene(Scene* scene);
        Scene* GetScene() const;
        Node* GetParent() const;
        virtual void update(sf::Time delta);
    protected:
        void SetParent(Node* parent);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        virtual void OnUpdate(sf::Time delta){};
        virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const {
        }
        virtual void PostDraw(sf::RenderTarget& target, sf::RenderStates states) const{
        }
    };

}

#endif	/* ENGINE_NODE_HPP */

