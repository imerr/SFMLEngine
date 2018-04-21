#ifndef ENGINE_TWEEN_HPP
#define ENGINE_TWEEN_HPP

#include <Engine/util/Event.hpp>
#include <functional>
#include <SFML/Graphics/Color.hpp>

namespace engine {
	typedef std::function<float(float from, float to, float time, float duration)> EasingFunction;

	template<typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, T>::type
	inline blendValueWithEasing(const T& from, const T& to, float time, float duration, const EasingFunction& f) {
		// We're potentially losing precision here, float should be more than good enough for any of our cases though
		return static_cast<T>(f(static_cast<float>(from), static_cast<float>(to), time, duration));
	};

	template<typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, sf::Vector2<T>>::type
	inline blendValueWithEasing(const sf::Vector2<T>& from, const sf::Vector2<T>& to, float time, float duration, const EasingFunction& f) {
		sf::Vector2<T> res;
		res.x = blendValueWithEasing(from.x, to.x, time, duration, f);
		res.y = blendValueWithEasing(from.y, to.y, time, duration, f);
		return res;
	};

	template<typename T>
	typename std::enable_if<std::is_same<T, sf::Color>::value, T>::type
	inline blendValueWithEasing(const T& from, const T& to, float time, float duration, const EasingFunction& f) {
		sf::Color res;
		res.r = blendValueWithEasing(from.r, to.r, time, duration, f);
		res.g = blendValueWithEasing(from.g, to.g, time, duration, f);
		res.b = blendValueWithEasing(from.b, to.b, time, duration, f);
		res.a = blendValueWithEasing(from.a, to.a, time, duration, f);
		return res;
	};

	// TODO(imer): move these away, they won't/can't be inlined anyways since we're storing pointers to them
	inline float EasingLinear(float from, float to, float time, float duration) {
		return (to - from) * time / duration + from;
	}

	class BaseTween {
	public:
		virtual void Update(float delta) = 0;
	};

	template<typename T>
	class Tween: public BaseTween {
	public:
	protected:
		T m_from;
		T m_to;
		float m_time;
		float m_duration;
		std::function<void(const T&)> m_callback;
		EasingFunction m_easingFunction;
		bool m_loop;
		bool m_loopReverse;
	public:
		Event<Tween<T>*> OnDone;
	public:
		Tween(const T& from, const T& to, float duration,
			  std::function<void(const T&)> callback,
			  EasingFunction easing = EasingLinear,
			  bool loop = false, bool loopReverse = true) :
				m_from(from), m_to(to), m_time(0), m_duration(duration), m_callback(callback),
				m_easingFunction(easing), m_loop(loop), m_loopReverse(loopReverse) { };

		Tween(const Tween<T>& o) {
			m_from = o.m_from;
			m_to = o.m_to;
			m_time = o.m_time;
			m_duration = o.m_duration;
			m_callback = o.m_callback;
			m_easingFunction = o.m_easingFunction;
			m_loop = o.m_loop;
			m_loopReverse = o.m_loopReverse;
		}

		Tween(const Tween<T>&& o) {
			m_from = o.m_from;
			m_to = o.m_to;
			m_time = o.m_time;
			m_duration = o.m_duration;
			m_callback = o.m_callback;
			m_easingFunction = o.m_easingFunction;
			m_loop = o.m_loop;
			m_loopReverse = o.m_loopReverse;
		}

		virtual void Update(float delta) {
			m_time += delta;
			if (m_time > m_duration) {
				if (!m_loop) {
					m_callback(m_to);
					OnDone.Fire(this);
					return;
				} else {
					m_time -= m_duration;
					if (m_loopReverse) {
						std::swap(m_from, m_to);
					}
				}
			}
			// its important to automatically have the compiler deduct the type for blendValueWithEasing
			// this allows us to do more template trickery
			m_callback(blendValueWithEasing(m_from, m_to, m_time, m_duration, m_easingFunction));
		}

		void Reset() {
			m_time = 0;
		}

		virtual ~Tween() {
			// Fire OnDone so we can delete this properly
			// The handlers are responsible for not messing up
			OnDone.Fire(this);
		}
	};

	template<typename T>
	Tween<T>* MakeValueTween(T& from, T to, float duration,
									  EasingFunction easing = EasingLinear,
									  bool loop = false, bool loopReverse = true) {
		return new Tween<T>(from, to, duration, [&from](const T& v) {
			from = v;
		}, easing, loop, loopReverse);
	}
}
#endif //ENGINE_TWEEN_HPP
