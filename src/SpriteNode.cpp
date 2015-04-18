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
#include "SFML/Graphics.hpp"
#include "Factory.hpp"
#include "Game.hpp"
namespace engine {

	Animation::Animation() : m_looping(false), m_speed(0), m_currentTime(0), m_currentFrame(0), OnOver([] {
	}) {

	}

	void Animation::SetLooping(bool looping) {
		m_looping = looping;
	}

	bool Animation::IsLooping() const {
		return m_looping;
	}

	std::vector<sf::IntRect>& Animation::GetFrames() {
		return m_frames;
	}

	void Animation::SetSpeed(float speed) {
		m_speed = speed;
	}

	float Animation::GetSpeed() const {
		return m_speed;
	}

	void Animation::Reset() {
		m_currentFrame = 0;
		m_currentTime = 0;
	}

	void Animation::AddFrame(const sf::IntRect& frame) {
		m_frames.push_back(frame);
	}

	void Animation::Update(float delta) {
		m_currentTime += delta;
		if (m_currentTime > m_speed) {

			m_currentFrame++;
			if (m_currentFrame >= m_frames.size()) {
				if (m_looping) {
					m_currentFrame = 0;
					m_currentTime = 0;
				} else {
					m_currentFrame--;
					OnOver();
				}
			} else {
				m_currentTime = 0;
			}
		}
	}

	const sf::IntRect& Animation::GetCurrentTexture() {
		return m_frames[m_currentFrame];
	}

	bool Animation::IsOver() {
		return m_currentTime > m_speed;
	}

	SpriteNode::SpriteNode(Scene* scene) : Node(scene), m_texture(0), m_currentAnimation("default"), m_animated(false) {
	}

	SpriteNode::~SpriteNode() {
		for (auto it = m_animations.begin(); it != m_animations.end();) {
			Animation* a = it->second;
			delete a;
			m_animations.erase(it++);
		}
	}

	void SpriteNode::OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
		if (m_animated) {
			std::lock_guard<std::recursive_mutex> lg(m_mutex);
			auto it = m_animations.find(m_currentAnimation);
			if (it != m_animations.end()) {
				it->second->Update(delta);
				if (it->second->IsOver() && m_animationWhenDone != "") {
					PlayAnimation(m_animationWhenDone);
				} else {
					m_textureRect = it->second->GetCurrentTexture();
					UpdateTexCoords();
				}
			}
		}
		states.texture = m_texture;
		target.draw(m_vertices, 4, sf::TrianglesStrip, states);

	}

	void SpriteNode::UpdatePosition() {
		m_vertices[0].position = sf::Vector2f(0, 0);
		m_vertices[1].position = sf::Vector2f(0, m_size.y);
		m_vertices[2].position = sf::Vector2f(m_size.x, 0);
		m_vertices[3].position = sf::Vector2f(m_size.x, m_size.y);
	}

	void SpriteNode::UpdateTexCoords() {
		float left = static_cast<float> (m_textureRect.left);
		float right = left + m_textureRect.width;
		float top = static_cast<float> (m_textureRect.top);
		float bottom = top + m_textureRect.height;
		if (m_flipped) {
			m_vertices[0].texCoords = sf::Vector2f(right, top);
			m_vertices[1].texCoords = sf::Vector2f(right, bottom);
			m_vertices[2].texCoords = sf::Vector2f(left, top);
			m_vertices[3].texCoords = sf::Vector2f(left, bottom);

		} else {
			m_vertices[0].texCoords = sf::Vector2f(left, top);
			m_vertices[1].texCoords = sf::Vector2f(left, bottom);
			m_vertices[2].texCoords = sf::Vector2f(right, top);
			m_vertices[3].texCoords = sf::Vector2f(right, bottom);

		}
	}

	void SpriteNode::SetTexture(std::string path, const sf::IntRect* rect) {
		sf::Texture* t = engine::ResourceManager::instance()->GetTexture(path);
		t->setRepeated(true);
		SetTexture(t, rect);
	}

	void SpriteNode::SetTexture(sf::Texture* texture, const sf::IntRect* rect) {
		m_texture = texture;
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
		if (!m_size.x && !m_size.y) {
			m_size.x = static_cast<float>(m_textureRect.width);
			m_size.y = static_cast<float>(m_textureRect.height);
		}
		UpdatePosition();
		UpdateTexCoords();
	}

	bool SpriteNode::initialize(Json::Value& root) {
		if (!Node::initialize(root)) {
			return false;
		}
		if (root.isMember("sprite")) {
			auto sprite = root["sprite"];
			if (sprite.isMember("texture")) {
				if (sprite.isMember("rect")) {
					sf::IntRect rect;
					if (sprite["rect"].isObject()) {
						rect.left = sprite["rect"].get("left", 0).asInt();
						rect.top = sprite["rect"].get("top", 0).asInt();
						rect.width = sprite["rect"].get("width", 0).asInt();
						rect.height = sprite["rect"].get("height", 0).asInt();
					} else {
						rect.left = sprite["rect"][0u].asInt();
						rect.top = sprite["rect"][1u].asInt();
						rect.width = sprite["rect"][2u].asInt();
						rect.height = sprite["rect"][3u].asInt();
					}
					SetTexture(sprite["texture"].asString(), &rect);
				} else {
					SetTexture(sprite["texture"].asString());
				}
			} else if (sprite.isMember("sheet")) {
				Json::Value sheet;
				if (sprite["sheet"].isString() && !Factory::LoadJson(sprite["sheet"].asString(), sheet)) {
					std::cerr << "Loading spritesheet json failed." << std::endl;
				} else if (sprite["sheet"].isObject()) {
					sheet = sprite["sheet"];
				}
				if (!sheet.isNull() && !sheet.empty()) {
					auto tex = sheet["sprites"][sprite.get("index", 0).asInt()];
					if (tex.empty() || tex.isNull()) {
						std::cerr << "Empty/Nonexistant sprite index " << sprite.get("index", 0) << std::endl;
					} else {
						sf::IntRect rect;
						rect.left = tex.get("left", 0).asInt();
						rect.top = tex.get("top", 0).asInt();
						rect.width = tex.get("width", 0).asInt();
						rect.height = tex.get("height", 0).asInt();
						SetTexture(sheet["texture"].asString(), &rect);
					}
					if (sprite["animations"].isObject()) {
						auto m = sprite["animations"].getMemberNames();
						for (size_t i = 0; i < m.size(); i++) {
							std::string aname = m[i];
							auto anim = sprite["animations"][aname];
							if (!anim["frames"].isArray()) {
								std::cerr << "Couldnt load animation, no frames" << std::endl;
								continue;
							}
							Animation* a = new Animation();
							a->SetSpeed(anim.get("speed", 1).asFloat());
							a->SetLooping(anim.get("loop", true).asBool());
							for (size_t o = 0; o < anim["frames"].size(); o++) {
								auto text = sheet["sprites"][anim["frames"][o].asInt()];
								if (text.isNull()) {
									std::cerr << "Frame " << o << "is invalid. Frame " << anim["frames"][o].asInt() << " doesnt exist." << std::endl;
									continue;
								}
								sf::IntRect rect;
								rect.left = text.get("left", 0).asInt();
								rect.top = text.get("top", 0).asInt();
								rect.width = text.get("width", 0).asInt();
								rect.height = text.get("height", 0).asInt();
								a->AddFrame(rect);
							}
							m_animations.insert(std::make_pair(aname, a));
							m_animated = true;
						}
					}
					if (sprite["animation"].isString()) {
						PlayAnimation(sprite["animation"].asString());
					}
				}
			}
		}
		return true;
	}

	uint8_t SpriteNode::GetType() const {
		return NT_SPRITE;
	}

	void SpriteNode::PlayAnimation(std::string name, std::string after) {
		std::lock_guard<std::recursive_mutex> lg(m_mutex);
		auto it = m_animations.find(name);
		if (it == m_animations.end()) {
			std::cerr << "Animation '" << name << "'could not be found";
			return;
		}
		m_animationWhenDone = after;
		it->second->Reset();
		m_currentAnimation = name;
	}

	Animation* SpriteNode::GetAnimation() {
		if (m_animations.find(m_currentAnimation) != m_animations.end()) {
			return m_animations[m_currentAnimation];
		} else {
			return nullptr;
		}
	}

	void SpriteNode::SetFlipped(bool flipped) {
		m_flipped = flipped;

	}
	void SpriteNode::SetSize(sf::Vector2f size) {
		Node::SetSize(size);
		UpdatePosition();
	}
}
