/* 
 * File:   ObjectPlacer.cpp
 * Author: iMer
 * 
 * Created on 7. Dezember 2014, 14:38
 */

#include "ObjectPlacer.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include "Factory.hpp"
namespace engine {

	ObjectPlacer::MouseHandler::MouseHandler(ObjectPlacer* placer) : m_placer(placer) {

	}

	void ObjectPlacer::MouseHandler::handle(const sf::Event::MouseButtonEvent& e) {
		auto m = m_placer->GetScene()->GetGame()->GetMousePosition();
		if (e.button == sf::Mouse::Left) {
			// int cast due to having fractions of a pixel being stupid
			m_placer->Place(static_cast<int> (m.x), static_cast<int> (m.y));
		} else if (e.button == sf::Mouse::Right) {
			m_placer->New(static_cast<int> (m.x), static_cast<int> (m.y));
		} else if (e.button == sf::Mouse::Middle) {
			m_placer->Remove();
		}
	}

	ObjectPlacer::KeyHandler::KeyHandler(ObjectPlacer* placer) : m_placer(placer) {

	}

	void ObjectPlacer::KeyHandler::handle(const sf::Event::KeyEvent& e) {
		if (e.code == sf::Keyboard::S) {
			m_placer->Save();
		}
		if (e.code == sf::Keyboard::Add) {
			sf::Vector2f p;
			if (m_placer->GetCurrentNode()) {
				p = m_placer->GetCurrentNode()->GetGlobalPosition();
			} else {
				p = m_placer->GetScene()->GetGame()->GetMousePosition();
			}
			m_placer->Remove();
			m_placer->Next();
			m_placer->New(static_cast<int>(p.x), static_cast<int>(p.y));
		}
		if (e.code == sf::Keyboard::Subtract) {
			sf::Vector2f p;
			if (m_placer->GetCurrentNode()) {
				p = m_placer->GetCurrentNode()->GetGlobalPosition();
			} else {
				p = m_placer->GetScene()->GetGame()->GetMousePosition();
			}
			m_placer->Remove();
			m_placer->Prev();
			m_placer->New(static_cast<int>(p.x), static_cast<int>(p.y));
		}
		Node* obj = m_placer->GetCurrentNode();
		if (obj) {
			auto p = obj->GetPosition();
			if (e.code == sf::Keyboard::Down) {
				obj->SetPosition(p.x, p.y + 1);
			}
			if (e.code == sf::Keyboard::Up) {
				obj->SetPosition(p.x, p.y - 1);
			}
			if (e.code == sf::Keyboard::Left) {
				obj->SetPosition(p.x - 1, p.y);
			}
			if (e.code == sf::Keyboard::Right) {
				obj->SetPosition(p.x + 1, p.y);
			}
		}

	}

	ObjectPlacer::DeleteHandler::DeleteHandler(ObjectPlacer* placer) : m_placer(placer) {

	}

	void ObjectPlacer::DeleteHandler::handle(const Node* n) {
		if (m_placer->GetCurrentNode() == n) {
			m_placer->SetCurrentNode(nullptr);
		}
	}

	ObjectPlacer::ObjectPlacer(Scene* scene) : Node(scene), m_current(0), m_mouseHandler(this), m_currentNode(nullptr), m_keyHandler(this), m_deleteHandler(this) {
		m_root["children"] = Json::arrayValue;
		scene->GetGame()->OnMouseClick.AddHandler(&m_mouseHandler);
		scene->GetGame()->OnKeyDown.AddHandler(&m_keyHandler);
	}

	ObjectPlacer::~ObjectPlacer() {
		m_scene->GetGame()->OnMouseClick.RemoveHandler(&m_mouseHandler);
		m_scene->GetGame()->OnKeyDown.RemoveHandler(&m_keyHandler);
		Save();
	}

	void ObjectPlacer::Place(float x, float y) {
		if (m_currentNode) {
			m_currentNode->SetPosition(x, y);
			if (m_currentNode->GetBody()) {
				m_currentNode->GetBody()->SetAwake(true);
			}
		}
	}

	void ObjectPlacer::Remove() {
		if (m_currentNode) {
			m_currentNode->OnDelete.RemoveHandler(&m_deleteHandler);
			delete m_currentNode;
			m_currentNode = nullptr;
		}
	}

	void ObjectPlacer::New(float x, float y, bool saveOld) {
		if (saveOld && m_currentNode) {
			size_t i = m_root["children"].size();
			m_root["children"][i] = Json::objectValue;
			m_root["children"][i]["childData"] = m_currentNode->GetFilename();
			m_root["children"][i]["position"][0u] = m_currentNode->GetPosition().x;
			m_root["children"][i]["position"][1u] = m_currentNode->GetPosition().y;
			m_currentNode->OnDelete.RemoveHandler(&m_deleteHandler);
		}
		Json::Value root;
		if (!Factory::LoadJson(m_objects[m_current], root)) {
			return;
		}
		auto& p = root["position"];
		if (!p.isArray()) {
			p = Json::arrayValue;
		}
		p[0u] = x;
		p[1u] = y;
		m_currentNode = Factory::CreateChild(root, this);
		if (m_currentNode) {
			AddNode(m_currentNode);
			m_currentNode->SetFilename(m_objects[m_current]);
			m_currentNode->SetPosition(x, y);
			m_currentNode->OnDelete.AddHandler(&m_deleteHandler);
		}
	}

	bool ObjectPlacer::initialize(Json::Value& root) {
		auto& o = root["objects"];
		if (o.isArray()) {
			for (size_t i = 0; i < o.size(); i++) {
				std::string object = o.get(i, "").asString();
				if (object != "") {
					m_objects.push_back(object);
				}
			}
		}
		return true;
	}

	void ObjectPlacer::Save() {
		std::ofstream d;
		d.open("out.json");
		if (!d.good()) {
			std::cerr << "Could not open out file: " << strerror(errno) << std::endl;
		} else {
			Json::StyledWriter w;
			d << w.write(m_root) << std::endl;
			std::cout << "Successfully saved to out.json" << std::endl;
		}
	}

}

