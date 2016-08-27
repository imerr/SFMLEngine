/*
 * File:   ParticleSystem.cpp
 * Author: iMer
 *
 * Created on 22. August 2014, 21:18
 */

#include "ParticleSystem.hpp"
#include "util/math.hpp"
#include "Scene.hpp"
#include "Factory.hpp"
#include <random>
#include <Engine/util/json.hpp>
#include "util/Random.hpp"

namespace engine {

	ParticleSystem::ParticleSystem(Scene *scene) : Node(scene), m_particleCount(0), m_currentIndex(0), m_rate(0),
												   m_burst(false), m_angle(0), m_spread(util::fPI * 2),
												   m_minVelocity(.5, .5, 0), m_maxVelocity(1, 1, 0), m_toRelease(0),
												   m_done(false) {
	}

	ParticleSystem::~ParticleSystem() {
		for (size_t i = 0; i < m_particles.size(); i++) {
			delete m_particles[i];
		}
		m_particles.clear();
	}

	void ParticleSystem::SetSpread(float spread) {
		m_spread = spread;
	}

	float ParticleSystem::GetSpread() const {
		return m_spread;
	}

	void ParticleSystem::SetAngle(float angle) {
		m_angle = angle;
	}

	float ParticleSystem::GetAngle() const {
		return m_angle;
	}

	void ParticleSystem::SetBurst(bool burst) {
		m_burst = burst;
	}

	bool ParticleSystem::IsBurst() const {
		return m_burst;
	}

	void ParticleSystem::SetRate(float rate) {
		m_rate = rate;
	}

	float ParticleSystem::GetRate() const {
		return m_rate;
	}

	void ParticleSystem::SetParticleCount(size_t particleCount) {
		if (m_particleConfig.isNull()) {
			std::cerr << "Particle config not set." << std::endl;
			return;
		}
		m_particleCount = particleCount;
		if (m_particleCount < m_particles.size()) {
			while (m_particleCount < m_particles.size()) {
				delete m_particles[m_particles.size()];
				m_particles.pop_back();
			}
		} else if (m_particleCount > m_particles.size()) {
			while (m_particleCount > m_particles.size()) {
				Node *particle = Factory::CreateChild(m_particleConfig, this);
				if (!particle) {
					std::cerr << "Failed to create particle from config." << std::endl;
					return;
				}
				if (!particle->GetBody()) {
					std::cerr << "Particle doesnt have a body." << std::endl;
					delete particle;
					return;
				}
				this->AddNode(particle);
				particle->GetBody()->SetTransform(b2Vec2(getPosition().x / m_scene->GetPixelMeterRatio(),
														 getPosition().y / m_scene->GetPixelMeterRatio()), 0);
				particle->SetActive(false);
				m_particles.push_back(particle);
			}
		}
	}

	size_t ParticleSystem::GetParticleCount() const {
		return m_particleCount;
	}

	void ParticleSystem::SetParticleConfig(std::string particleConfig) {
		Factory::LoadJson(particleConfig, m_particleConfig);
	}

	void ParticleSystem::OnUpdate(sf::Time interval) {
		if (!m_particleCount || m_burst && m_done) {
			return;
		}
		util::RandomFloat<float> angle(m_angle - (m_spread / 2), m_angle + (m_spread / 2));
		util::RandomFloat<float> rx(m_minVelocity.x, m_maxVelocity.x);
		util::RandomFloat<float> ry(m_minVelocity.y, m_maxVelocity.y);
		util::RandomFloat<float> rr(m_minVelocity.z, m_maxVelocity.z);
		util::RandomFloat<float> sx(-m_emitterSize.x/2, m_emitterSize.x/2);
		util::RandomFloat<float> sy(-m_emitterSize.y/2, m_emitterSize.y/2);

		if (m_burst) {
			if (m_particles.size() != m_particleCount) {
				SetParticleCount(m_particleCount);
			}
			m_done = true;
			m_toRelease = m_particleCount;
		} else {
			m_toRelease += interval.asSeconds() * m_rate;
		}
		for (m_toRelease; m_toRelease >= 1; m_toRelease--) {
			float a = angle();
			m_particles[m_currentIndex]->SetActive(true);
			m_particles[m_currentIndex]->GetBody()->SetTransform(
				b2Vec2((sx() + GetGlobalPosition().x) / m_scene->GetPixelMeterRatio(),
					   (sy() + GetGlobalPosition().y) / m_scene->GetPixelMeterRatio()), a);
			m_particles[m_currentIndex]->GetBody()->SetLinearVelocity(b2Vec2(cosf(a) * rx(), sinf(a) * ry()));
			m_particles[m_currentIndex]->GetBody()->SetAngularVelocity(rr());
			m_currentIndex++;
			if (m_currentIndex >= m_particleCount) {
				m_currentIndex = 0;
			}
		}
	}

	bool ParticleSystem::initialize(Json::Value &root) {
		if (!Node::initialize(root)) {
			return false;
		}
		if (root["particleConfig"].isString()) {
			Factory::LoadJson(root["particleConfig"].asString(), m_particleConfig);
		} else {
			m_particleConfig = root["particleConfig"];
		}
		m_rate = root.get("rate", 1).asFloat();
		m_burst = root.get("burst", false).asBool();
		if (!m_burst) {
			util::RandomFloat<float> r(m_rate/2, m_rate);
			m_toRelease = 1/r();
		}
		if (!m_burst || root.get("load", false).asBool()) {
			// performance optimization if burst and the system never gets used
			SetParticleCount(root.get("particleCount", 10).asUInt());
		} else {
			m_particleCount = root.get("particleCount", 10).asUInt();
		}
		m_angle = root.get("angle", 0).asFloat() * util::fPI / 180;
		m_spread = root.get("spread", 360).asFloat() * util::fPI / 180;
		m_emitterSize = vector2FromJson<float>(root["emitterSize"]);

		if (root["minVelocity"].isArray()) {
			m_minVelocity.x = root["minVelocity"].get(0u, .5 * m_scene->GetPixelMeterRatio()).asFloat() /
							  m_scene->GetPixelMeterRatio();
			m_minVelocity.y = root["minVelocity"].get(1u, .5 * m_scene->GetPixelMeterRatio()).asFloat() /
							  m_scene->GetPixelMeterRatio();
			m_minVelocity.z = root["minVelocity"].get(2u, 0).asFloat() * util::fPI / 180;
		}


		if (root["maxVelocity"].isArray()) {
			m_maxVelocity.x = root["maxVelocity"].get(0u, 1 * m_scene->GetPixelMeterRatio()).asFloat() /
							  m_scene->GetPixelMeterRatio();
			m_maxVelocity.y = root["maxVelocity"].get(1u, 1 * m_scene->GetPixelMeterRatio()).asFloat() /
							  m_scene->GetPixelMeterRatio();
			m_maxVelocity.z = root["maxVelocity"].get(2u, 0).asFloat() * util::fPI / 180;
		}
		return true;
	}

	uint8_t ParticleSystem::GetType() const {
		return NT_PARTICLESYSTEM;
	}
	void ParticleSystem::Reset() {
		m_done = false;
	}
}