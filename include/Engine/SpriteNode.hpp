#ifndef ENGINE_SPRITENODE_HPP
#define ENGINE_SPRITENODE_HPP

#include "Node.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <functional>

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

		std::function<void(void)> OnOver;
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
		bool m_vFlipped;
	public:
		SpriteNode(Scene* scene);

		virtual ~SpriteNode();

		void SetTexture(std::string path, const sf::IntRect* rect = nullptr);

		void SetTexture(sf::Texture* texture, const sf::IntRect* rect = nullptr);

		virtual bool initialize(Json::Value& root);

		virtual uint8_t GetType() const;

		void PlayAnimation(std::string name, std::string after = "");

		Animation* GetAnimation();

		virtual void SetFlipped(bool flipped);

		virtual void SetVFlipped(bool flipped);

		virtual void SetSize(sf::Vector2f size);

		std::string GetAnimationName() const {
			return m_currentAnimation;
		}

		sf::IntRect& GetTextureRect() {
			return m_textureRect;
		}

		bool IsVFlipped() const {
			return m_vFlipped;
		}

		void SetColor(const sf::Color& color) {
			m_vertices[0].color = color;
			m_vertices[1].color = color;
			m_vertices[2].color = color;
			m_vertices[3].color = color;
		}

	protected:
		void UpdatePosition();

		void UpdateTexCoords();

	protected:
		virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta);
	};
}
#endif

