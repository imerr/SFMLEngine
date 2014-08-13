/* 
 * File:   Scene.hpp
 * Author: iMer
 *
 * Created on 3. Juli 2014, 01:01
 */

#ifndef ENGINE_SCENE_HPP
#define	ENGINE_SCENE_HPP
#include "Node.hpp"
#include "LightSystem.hpp"
namespace engine {
    class Game;
    class Scene: public Node {
    protected:
        Game* m_game;
    public:
        Scene();
        Scene(const Scene& orig);
        virtual ~Scene();
        void SetGame(Game* game);
        Game* GetGame() const;
    private:
        virtual void OnUpdate(sf::Time delta);
        virtual void PostDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#endif	/* ENGINE_SCENE_HPP */

