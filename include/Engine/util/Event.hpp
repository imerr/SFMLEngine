/* 
 * File:   Event.hpp
 * Author: iMer
 *
 * Created on 23. August 2014, 17:44
 */

#ifndef ENGINE_UTIL_EVENT_HPP
#define    ENGINE_UTIL_EVENT_HPP

#include <list>

namespace engine {
	class BaseEventHandler {
	};

	template<typename... T>
	class EventHandler : public BaseEventHandler {
	public:
		virtual void handle(T...)=0;
	};

	template<typename... T>
	class EventHandlerWrapper : public EventHandler<T...> {
		std::function<void(T...)> func;
	public:
		EventHandlerWrapper(std::function<void(T...)> t) : func(t) {}

		virtual void handle(T... args) {
			func(args...);
		};
	};


	template<typename... T>
	class Event {
	protected:
		std::list<EventHandler<T...>*> m_callbacks;
	public:

		void AddHandler(EventHandler<T...>* handler) {
			m_callbacks.push_back(handler);
		}

		template<class D>
		EventHandler<T...>* MakeHandler(D handler) {
			EventHandler<T...>* wrap = new EventHandlerWrapper<T...>(handler);
			m_callbacks.push_back(wrap);
			return wrap;
		}

		void RemoveHandler(BaseEventHandler* handler) {
			// allow passing in base class for convenience and up-cast then
			// We dont dereference the pointer so nothing should go wrong even if bogus gets passed in
			m_callbacks.remove(static_cast<EventHandler<T...>*>(handler));
		}

		void Fire(T... args) {
			for (auto it = m_callbacks.begin(); it != m_callbacks.end();) {
				(*it++)->handle(args...);
			}
		}
	};
}

#endif
