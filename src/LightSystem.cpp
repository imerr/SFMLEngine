/*
 * File:   LightSystem.cpp
 * Author: iMer
 *
 * Created on 17. August 2014, 10:39
 */

#include "LightSystem.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include <iostream>

namespace engine {

	void applyShader(const sf::Shader& shader, sf::RenderTarget& output) {
		sf::Vector2f outputSize(static_cast<float>(output.getSize().x),
								static_cast<float>(output.getSize().y));
		sf::VertexArray vertices(sf::TrianglesStrip, 4);
		vertices[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(0, 1));
		vertices[1] = sf::Vertex(sf::Vector2f(outputSize.x, 0), sf::Vector2f(1, 1));
		vertices[2] = sf::Vertex(sf::Vector2f(0, outputSize.y), sf::Vector2f(0, 0));
		vertices[3] = sf::Vertex(sf::Vector2f(outputSize), sf::Vector2f(1, 0));
		sf::RenderStates states;
		states.shader = &shader;
		states.blendMode = sf::BlendNone;
		output.draw(vertices, states);
	}

	LightSystem::LightSystem(Scene* scene) : m_scene(scene), m_ambientColor(sf::Color::White), m_needsUpdate(true),
											 m_enabled(true) {
		if (!sf::Shader::isAvailable()) {
			std::cerr << "Shaders are not available" << std::endl;
			m_available = false;
		} else {
			m_available = true;
			m_blurShader.loadFromFile("assets/shader/fullpass.vert", "assets/shader/blur.frag");

		}
		auto size = m_scene->GetGame()->GetWindow()->getView().getSize();
		m_buffer.create(static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y));
		m_pingPongBuffer.create(static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y));
		m_buffer.setActive(false);
		m_pingPongBuffer.setActive(false);
	}

	bool LightSystem::update(sf::Time interval) {
		m_needsUpdate = true;
		return false;
	}

	void LightSystem::draw(sf::RenderTarget& target, sf::RenderStates states) {
		if (!m_enabled) {
			return;
		}
		std::lock_guard<std::recursive_mutex> lg(m_drawLock);
		sf::Sprite s;
		if (m_needsUpdate) {
			m_needsUpdate = false;
			m_buffer.clear(m_ambientColor);
			states.blendMode = sf::BlendAdd;
			std::for_each(m_lights.begin(), m_lights.end(), [this, &states](Light* light) {
				light->DrawLight(m_buffer, states);
			});
			m_buffer.display();
			if (m_available) {
				auto textureSize = m_buffer.getSize();
				for (size_t i = 0; i < blurPasses; i++) {
					m_blurShader.setParameter("offsetFactor", sf::Vector2f(0.0f, 2.f / textureSize.y));
					m_blurShader.setParameter("source", m_buffer.getTexture());
					applyShader(m_blurShader, m_pingPongBuffer);
					m_blurShader.setParameter("offsetFactor", sf::Vector2f(2.0f / textureSize.x, 0.0f));
					m_blurShader.setParameter("source", m_pingPongBuffer.getTexture());
					applyShader(m_blurShader, m_buffer);
					m_buffer.display();
				}
			}
		}
		sf::Transformable tr;
		auto window = m_scene->GetGame()->GetWindow();
		tr.setPosition(window->getView().getCenter().x - (window->getView().getSize().x / 2),
					   window->getView().getCenter().y - (window->getView().getSize().y / 2));
		states.transform *= tr.getTransform();
		states.blendMode = sf::BlendMultiply;
		s.setTexture(m_buffer.getTexture());
		target.draw(s, states);
	}

	void LightSystem::SetAmbientColor(sf::Color ambientColor) {

		m_ambientColor = ambientColor;
	}

	sf::Color LightSystem::GetAmbientColor() const {

		return m_ambientColor;
	}

	void LightSystem::SetEnabled(bool enabled) {
		m_enabled = enabled;
	}

	bool LightSystem::IsEnabled() const {
		return m_enabled;
	}

	void LightSystem::AddLight(Light* light) {
		m_lights.push_back(light);
	}

	void LightSystem::RemoveLight(Light* light) {
		// bleh
		std::lock_guard<std::recursive_mutex> lg(m_drawLock);
		m_lights.remove(light);
	}
}
