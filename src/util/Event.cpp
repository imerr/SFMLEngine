#include "util/Event.hpp"
#include "Node.hpp"

namespace engine {
	namespace {
		void WalkNode(Node* node, std::function<void(Node*)> f, bool up = true, Node* startNode = nullptr) {
			for (auto child : node->GetChildren()) {
				if (child == startNode) {
					continue;
				}
				f(child);
				WalkNode(child, f, false, startNode ? startNode : node);
			}
			if (up) {
				// walk up
				if (node->GetParent() && node->GetParent() != node) {
					WalkNode(node->GetParent(), f, true, startNode ? startNode : node);
				}
			}
		}
	}
	void SortHandlerVector(Node* node, std::vector<BaseEventHandler*>& canHandle) {
		std::vector<BaseEventHandler*> sorted;
		sorted.reserve(canHandle.size());
		WalkNode(node, [&sorted, &canHandle](Node* n) {
			for (auto it = canHandle.begin(); it != canHandle.end(); it++) {
				if (n == (*it)->GetOwner()) {
					sorted.push_back(*it);
					canHandle.erase(it);
					break;
				}
			}
		});
		// fill in all the remaining ones that dont match any node
		for (auto h : canHandle) {
			sorted.push_back(h);
		}
		canHandle.swap(sorted);
	}
}