#ifndef ENGINE_UTIL_EVENT_HPP
#define ENGINE_UTIL_EVENT_HPP

#include <functional>
#include <list>
#include <vector>

namespace engine {
	class BaseEventHandler {
	protected:
		void* owner;
	public:
		BaseEventHandler(void* owner = nullptr) : owner(owner) {};
		virtual ~BaseEventHandler() {};
		void* GetOwner() {
			return owner;
		}
	};

	template<typename ReturnType, typename... T>
	class EventHandler : public BaseEventHandler {
	public:
		EventHandler(void* owner = nullptr) : BaseEventHandler(owner) {};
		virtual ~EventHandler() {}

		virtual ReturnType handle(T...) = 0;

		virtual bool CanHandle(T...) {
			return true;
		}
	};

	template<typename ReturnType, typename... T>
	class EventHandlerWrapper : public EventHandler<ReturnType, T...> {
		std::function<ReturnType(T...)> func;
		std::function<bool(T...)> canFunc;
	public:
		EventHandlerWrapper(std::function<ReturnType(T...)> t, void* owner = nullptr) : EventHandler(owner), func(t) {}

		EventHandlerWrapper(std::function<ReturnType(T...)> canFunc,
							std::function<ReturnType(T...)> handleFunc,
							void* owner = nullptr) : EventHandler(owner), canFunc(canFunc), func(handleFunc) {}
		virtual ~EventHandlerWrapper() {}

		virtual ReturnType handle(T... args) {
			return func(args...);
		};

		virtual bool CanHandle(T... args) {
			return canFunc ? canFunc(args...) : true;
		}
	};

	class Node;

	void SortHandlerVector(Node*, std::vector<BaseEventHandler*>& canHandle);

	template<typename... T>
	class Event {
	protected:
		std::list<EventHandler<void, T...>*> m_callbacks;
	public:

		void AddHandler(EventHandler<void, T...>* handler) {
			m_callbacks.push_back(handler);
		}

		template<class D>
		EventHandler<void, T...>* MakeHandler(D handler, void* owner = nullptr, bool front = false) {
			EventHandler<void, T...>* wrap = new EventHandlerWrapper<void, T...>(handler, owner);
			if (front) {
				m_callbacks.insert(m_callbacks.begin(), wrap);
			} else {
				m_callbacks.push_back(wrap);
			}
			return wrap;
		}

		void RemoveHandler(BaseEventHandler* handler) {
			// allow passing in base class for convenience and up-cast then
			// We don't dereference the pointer so nothing should go wrong even if bogus gets passed in
			m_callbacks.remove(static_cast<EventHandler<void, T...>*>(handler));
		}

		void Fire(T... args) {
			for (auto it = m_callbacks.begin(); it != m_callbacks.end();) {
				if ((*it)->CanHandle(args...)) {
					(*it++)->handle(args...);
				}
			}
		}
	};

	template<typename... T>
	class CancelableEvent {
	protected:
		std::list<EventHandler<bool, T...>*> m_callbacks;
		EventHandler<bool, T...>* m_lastHandler;
	public:
		CancelableEvent() : m_lastHandler(nullptr) {}

		EventHandler<bool, T...>* GetLastHandler() {
			return m_lastHandler;
		}

		void AddHandler(EventHandler<bool, T...>* handler) {
			m_callbacks.push_back(handler);
		}

		template<class D, class F>
		EventHandler<bool, T...>* MakeHandler(D canHandle, F handler, void* owner, bool front = false) {
			EventHandler<bool, T...>* wrap = new EventHandlerWrapper<bool, T...>(canHandle, handler, owner);
			if (front) {
				m_callbacks.insert(m_callbacks.begin(), wrap);
			} else {
				m_callbacks.push_back(wrap);
			}
			return wrap;
		}

		void RemoveHandler(BaseEventHandler* handler) {
			// allow passing in base class for convenience and up-cast then
			// We don't dereference the pointer so nothing should go wrong even if bogus gets passed in
			auto h = static_cast<EventHandler<bool, T...>*>(handler);

			m_callbacks.remove(h);

			if (m_lastHandler == h) {
				m_lastHandler = nullptr;
			}
		}

		void Fire(Node* from, T... args) {
			std::vector<BaseEventHandler*> canHandle;
			for (auto callback : m_callbacks) {
				if (callback->CanHandle(args...)) {
					canHandle.push_back(callback);
				}
			}

			// sort them so the closest node gets called first
			SortHandlerVector(from, canHandle);

			for (auto handler : canHandle) {
				auto h = static_cast<EventHandler<bool, T...>*>(handler);
				if (h->handle(args...)) {
					m_lastHandler = h;
					break;
				}
			}
		}

	};
}

#endif
