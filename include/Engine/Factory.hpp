#ifndef ENGINE_FACTORY_HPP
#define ENGINE_FACTORY_HPP

#include "Scene.hpp"
#include "SpriteNode.hpp"
#include <json/json.h>
#include <iostream>
#include <fstream>
#include <map>

namespace engine {

	class Factory {
	protected:
		static std::map<std::string, std::function<Node*(Json::Value& root, Node* parent) >> m_types;
	public:
		static void RegisterType(std::string name, std::function<Node*(Json::Value& root, Node* parent)> callback);

		static void RemoveType(std::string name);

		static bool LoadJson(std::string filename, Json::Value& root);

		template<class T, typename... args>
		static T* create(std::string config, args... params) {
			Json::Value root;
			if (!LoadJson(config, root)) {
				return nullptr;
			}
			T* d = createJson<T>(root, params...);
			if (d) {
				d->SetFilename(config);
			}
			return d;
		}

		template<class T, typename... args>
		static T* createJson(Json::Value& root, args... params) {
			T* thing = new T(params...);
			if (thing->initialize(root)) {
				if (root.isMember("children") && root["children"].isArray()) {
					for (Json::ArrayIndex i = 0; i < root["children"].size(); i++) {
						auto child = root["children"][i];
						if (!child.isObject()) {
							std::cerr << "Child has to be object" << std::endl;
							continue;
						}
						Node* nchild = CreateChild(child, thing);
					}
				}
				thing->OnInitializeDone();
				return thing;
			}
			delete thing;
			return nullptr;
		}

		template<class T>
		static Node* CreateChildNode(Json::Value& root, Node* parent = nullptr) {
			T* thing = new T(parent->GetScene());
			// Do this so we can use it during initialize, SetParent only sets the pointer m_parent, which gets overwritten once we do AddNode anyways - if creation fails nothing happens
			thing->SetParent(parent);
			if (thing->initialize(root)) {
				if (root.isMember("children")) {
					if (!MakeChildren(root["children"], thing)) {
						std::cerr << "Failed to make children" << std::endl;
					}
				}
				return thing;
			}
			delete thing;
			return nullptr;
		}

		static Node* CreateChild(Json::Value root, Node* parent);

		static Node* CreateChildFromFile(std::string file, Node* parent);

		static bool MakeChildren(Json::Value& c, Node* parent);

		static void MergeJson(Json::Value& a, Json::Value& b);

	private:

		Factory() {

		}

	};
}

#endif

