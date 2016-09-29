#include "Scrollable.hpp"
#include <SFML/OpenGL.hpp>
#include <Engine/util/json.hpp>
#include <iostream>
#include <Engine/util/misc.hpp>
#include "Game.hpp"

namespace engine {
	// TODO(imer): make this configurable
	const float scrollSpeedMultiplier = 20.0f;

	Scrollable::Scrollable(Scene* scene) : Node(scene), m_scrollHandler(this), m_globalEvents(false) {
		// TODO(imer): touch dragging
		// TODO(imer): smoothing (?)
		// TODO(imer): (optional) mouse dragging
		// TODO(imer): (optional) scroll bars
		// TODO(imer): (optional) up and down buttons
		GetScene()->GetGame()->OnMouseScroll.AddHandler(&m_scrollHandler);
	}

	Scrollable::~Scrollable() {
		GetScene()->GetGame()->OnMouseScroll.RemoveHandler(&m_scrollHandler);
	}

	void Scrollable::OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
		glEnable(GL_SCISSOR_TEST);
		auto window = GetScene()->GetGame()->GetWindow();
		auto view = window->getView();
		auto pos = m_parent->GetGlobalPosition() + m_positionOffset - view.getCenter()
				   + sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2);
		sf::Vector2f viewScale(window->getSize().x / view.getSize().x,
							   window->getSize().y / view.getSize().y);
		glScissor(static_cast<int>(viewScale.x * pos.x),
				  window->getSize().y - static_cast<int>(viewScale.y * (pos.y + m_viewSize.y)),
				  static_cast<int>(m_viewSize.x * viewScale.x),
				  static_cast<int>(m_viewSize.y * viewScale.y)
		);
	}

	void Scrollable::PostDraw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
		glDisable(GL_SCISSOR_TEST);
	}

	bool Scrollable::initialize(Json::Value& root) {
		if (!Node::initialize(root)) {
			return false;
		}
		m_positionOffset = vector2FromJson<float>(root["position"]);
		m_viewSize = vector2FromJson<int>(root["viewSize"]);
		m_globalEvents = root.get("globalEvents", false).asBool();
		return true;
	}

	void Scrollable::Scroll(float x, float y) {
		auto pos = GetPosition();
		SetPosition(
				clamp(m_positionOffset.x - m_size.x + m_viewSize.x, pos.x + x, m_positionOffset.x),
				clamp(m_positionOffset.y - m_size.y + m_viewSize.y, pos.y + y, m_positionOffset.y)
		);
	}


	bool Scrollable::ScrollHandler::handle(const sf::Event::MouseWheelScrollEvent& e) {
		scrollable->Scroll(
				e.wheel == sf::Mouse::HorizontalWheel ? e.delta * scrollSpeedMultiplier : 0,
				e.wheel == sf::Mouse::VerticalWheel ? e.delta * scrollSpeedMultiplier : 0
		);
		return true;
	}

	bool Scrollable::ScrollHandler::CanHandle(const sf::Event::MouseWheelScrollEvent& e) {
		if (!scrollable->HandleGlobalEvents()) {
			auto pos = scrollable->GetParent()->GetGlobalPosition() + scrollable->GetPositionOffset();
			sf::FloatRect r(pos, sf::Vector2f(scrollable->GetViewSize().x, scrollable->GetViewSize().y));
			auto clickpos = scrollable->GetScene()->GetGame()->GetWindow()->mapCoordsToPixel(sf::Vector2f(e.x, e.y));
			return r.contains(clickpos.x, clickpos.y);
		}
		return true;
	}

	Scrollable::ScrollHandler::ScrollHandler(Scrollable* scrollable) : scrollable(scrollable) {}
}
