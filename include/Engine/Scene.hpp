/* 
 * File:   Scene.hpp
 * Author: iMer
 *
 * Created on 3. Juli 2014, 01:01
 */

#ifndef ENGINE_SCENE_HPP
#define    ENGINE_SCENE_HPP

#include "Node.hpp"
#include "util/Event.hpp"
#include "Box2D/Box2D.h"
#include "util/Box2dDebugDraw.hpp"
#include "LightSystem.hpp"

namespace engine {
	class Game;

	class Light;

	class SceneContactListener : public b2ContactListener {
		Scene* m_scene;
	public:
		SceneContactListener(Scene* scene);

		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

		virtual void BeginContact(b2Contact* contact);

		virtual void EndContact(b2Contact* contact);

		virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	};

	class Scene : public Node {
	public:
		static b2Vec2 default_gravity;
	protected:
		Game* m_game;
		b2World* m_world;
		float m_pixToM;
		Box2dDebugDraw m_debugDraw;
		std::recursive_mutex m_mutexDebug;
		LightSystem m_lightSystem;
		bool m_debug;
		Node* m_ui;
		SceneContactListener m_contactListener;
	public:
		Event<b2Contact*, const b2Manifold*> OnContactPreSolve;
		Event<b2Contact*, bool> OnContact;
		Event<b2Contact*, const b2ContactImpulse*> OnContactPostSolve;
	public:
		Scene(Game* game);

		virtual ~Scene();

		void SetGame(Game* game);

		Game* GetGame() const;

		b2World* GetWorld();

		float MeterToPixel(float m);

		float GetPixelMeterRatio() const;

		void AddLight(Light* light);

		void RemoveLight(Light* light);

		LightSystem* GetLightSystem();

		void SetDebug(bool debug);

		bool IsDebug() const;

		virtual uint8_t GetType() const;

		virtual bool initialize(Json::Value& root);

		void SetUi(Node* ui) {
			m_ui = ui;
		}

		Node* GetUi() const {
			return m_ui;
		}

	protected:
		virtual void OnUpdate(sf::Time interval);

		virtual void PostDraw(sf::RenderTarget& target, sf::RenderStates states, float delta);
	};
}

#endif	/* ENGINE_SCENE_HPP */

