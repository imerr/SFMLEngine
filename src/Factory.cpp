#include <Engine/Scrollable.hpp>
#include <Engine/Factory.hpp>
#include <Engine/ParticleSystem.hpp>
#include <Engine/Text.hpp>
#include <Engine/Button.hpp>
#include <Engine/ObjectPlacer.hpp>
#include <Engine/ParallaxBackground.hpp>

namespace engine {
	std::map<std::string, std::function<Node*(Json::Value& root, Node* parent) >> Factory::m_types = {
			std::make_pair(std::string("node"),
						   std::function<Node*(Json::Value& root, Node* parent)>(Factory::CreateChildNode<Node>)),
			std::make_pair(std::string("sprite"),
						   std::function<Node*(Json::Value& root, Node* parent)>(Factory::CreateChildNode<SpriteNode>)),
			std::make_pair(std::string("light"),
						   std::function<Node*(Json::Value& root, Node* parent)>(Factory::CreateChildNode<Light>)),
			std::make_pair(std::string("text"),
						   std::function<Node*(Json::Value& root, Node* parent)>(Factory::CreateChildNode<Text>)),
			std::make_pair(std::string("button"),
						   std::function<Node*(Json::Value& root, Node* parent)>(Factory::CreateChildNode<Button>)),
			std::make_pair(std::string("objectPlacer"),
						   std::function<Node*(Json::Value& root, Node* parent)>(
								   Factory::CreateChildNode<ObjectPlacer>)),
			std::make_pair(std::string("parallaxBackground"), std::function<Node*(Json::Value& root, Node* parent)>(
					Factory::CreateChildNode<ParallaxBackground>)),
			std::make_pair(std::string("scrollable"),
						   std::function<Node*(Json::Value& root, Node* parent)>(Factory::CreateChildNode<Scrollable>)),
			std::make_pair(std::string("particlesystem"),
						   std::function<Node*(Json::Value& root, Node* parent)>(
								   Factory::CreateChildNode<ParticleSystem>))
	};

	void Factory::RegisterType(std::string name, std::function<Node*(Json::Value& root, Node* parent)> callback) {
		m_types.insert(std::make_pair(name, callback));
	}

	void Factory::RemoveType(std::string name) {
		m_types.erase(name);
	}

	bool Factory::LoadJson(std::string filename, Json::Value& root) {
		Json::Reader reader;
		sf::FileInputStream jconfig;
		if (!jconfig.open(filename)) {
			std::cerr << "Could not open config file '" << filename << "': " << strerror(errno) << std::endl;
			return false;
		}
		std::vector<char> tmp;
		tmp.reserve(jconfig.getSize());
		jconfig.read(tmp.data(), jconfig.getSize());
		if (!reader.parse(tmp.data(), tmp.data() + jconfig.getSize(), root)) {
			std::cerr << "Couldn't parse config" << std::endl << reader.getFormattedErrorMessages() << std::endl;
			return false;
		}
		return true;
	}

	Node* Factory::CreateChild(Json::Value root, Node* parent) {
		Json::Value childData;
		if (root["childData"].isString()) {
			if (!LoadJson(root["childData"].asString(), childData)) {
				std::cerr << "Couldn't load childData from file" << std::endl;
				return nullptr;
			}
		} else {
			childData = root["childData"];
		}
		MergeJson(childData, root);
		std::string type = childData.get("type", "node").asString();
		auto it = m_types.find(type);
		if (it == m_types.end()) {
			std::cerr << "Type '" << type << "' was not registered. Cant load child." << std::endl;
			return nullptr;
		}
		Node* c = it->second(childData, parent);
		if (!c) {
			return nullptr;
		}
		if (root["childData"].isString()) {
			c->SetFilename(root["childData"].asString());
		}
		return c;
	}

	Node* Factory::CreateChildFromFile(std::string file, Node* parent) {
		Json::Value root;
		if (!Factory::LoadJson(file, root)) {
			return nullptr;
		}
		std::string type = root.get("type", "node").asString();
		auto it = m_types.find(type);
		if (it == m_types.end()) {
			std::cerr << "Type '" << type << "' was not registered. Cant load child." << std::endl;
			return nullptr;
		}
		Node* c = it->second(root, parent);
		if (!c) {
			return nullptr;
		}
		c->SetFilename(file);
		parent->AddNode(c);
		c->OnInitializeDone();
		return c;
	}

	bool Factory::MakeChildren(Json::Value& children, Node* parent) {
		if (!children.isArray()) {
			std::cerr << "Children is expected to be an array";
			return false;
		}
		for (size_t i = 0; i < children.size(); i++) {
			auto child = children[i];
			if (!child.isObject()) {
				std::cerr << "Child has to be object" << std::endl;
				continue;
			}
			Node* nchild = CreateChild(child, parent->GetScene());
			if (nchild) {
				parent->AddNode(nchild);
				nchild->OnInitializeDone();
			}
		}
		return true;
	}


	void Factory::MergeJson(Json::Value& a, Json::Value& b) { // http://stackoverflow.com/a/23860017/1318435
		if (!b.isObject()) return;

		for (const auto& key : b.getMemberNames()) {
			if (a[key].isObject()) {
				MergeJson(a[key], b[key]);
			} else {
				a[key] = b[key];
			}
		}
	}
}

