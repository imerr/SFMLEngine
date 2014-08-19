/* 
 * File:   LightSystem.hpp
 * Author: iMer
 *
 * Created on 17. August 2014, 10:39
 */

#ifndef LIGHTSYSTEM_HPP
#define	LIGHTSYSTEM_HPP
#include <SFML/Graphics.hpp>
#include "Light.hpp"
#include <atomic>
namespace engine {
    class Scene;
    class LightSystem : public sf::NonCopyable {
        const static size_t blurPasses=1;
    protected:
        Scene* m_scene;
        sf::RenderTexture m_buffer;
        sf::RenderTexture m_pingPongBuffer;
        sf::Shader m_blurShader;
        std::list<Light*> m_lights;
        sf::Color m_ambientColor;
        std::atomic<bool> m_needsUpdate;
    public:
        LightSystem(Scene*);
        virtual ~LightSystem();
        void AddLight(Light* light);
        void RemoveLight(Light* light);
        virtual void update(sf::Time interval);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates state);
        void SetAmbientColor(sf::Color ambientColor);
        sf::Color GetAmbientColor() const;
    private:

    };
}

#endif	/* LIGHTSYSTEM_HPP */

