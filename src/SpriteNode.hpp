/* 
 * File:   SpriteNode.hpp
 * Author: iMer
 *
 * Created on 3. Juli 2014, 01:51
 */

#ifndef SPRITENODE_HPP
#define	SPRITENODE_HPP

#include "Node.hpp"
#include "SFML/Graphics/Texture.hpp"
namespace engine {

    class Animation {
    protected:
        std::vector<sf::IntRect> m_frames;
        bool m_looping;
        float m_speed;
        float m_currentTime;
        size_t m_currentFrame;
    public:
        Animation();
        void SetLooping(bool looping);
        bool IsLooping() const;
        std::vector<sf::IntRect>& GetFrames();
        void SetSpeed(float speed);
        float GetSpeed() const;
        void AddFrame(const sf::IntRect& frame);
        void Reset();
        void Update(float delta);
        const sf::IntRect& GetCurrentTexture();
        bool IsOver();
    };

    class SpriteNode : public Node {
    protected:
        const sf::Texture* m_texture;
        sf::Vertex m_vertices[4];
        sf::IntRect m_textureRect;
        std::map<std::string, Animation*> m_animations;
        std::string m_currentAnimation;
        bool m_animated;
        std::string m_animationWhenDone;
        bool m_flipped;
    public:
        SpriteNode(Scene* scene);
        virtual ~SpriteNode();
        void SetTexture(std::string path, const sf::IntRect* rect = nullptr);
        void SetTexture(sf::Texture* texture, const sf::IntRect* rect = nullptr);
        virtual bool initialize(Json::Value& root);
        virtual uint8_t GetType() const;
        void PlayAnimation(std::string name, std::string after="");
    protected:
        void UpdatePosition();
        void UpdateTexCoords();
    private:
        virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta);
    };
}
#endif	/* SPRITENODE_HPP */

