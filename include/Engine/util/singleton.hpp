/* 
 * File:   singleton.hpp
 * Author: iMer
 *
 * Created on 3. Juli 2014, 16:34
 */

#ifndef SINGLETON_HPP
#define    SINGLETON_HPP
namespace engine {
	template<typename T>
	class singleton {
	public:
		static T* ms_singleton;

		static T* instance() {
			if (!ms_singleton) {
				ms_singleton = new T();
			}
			return ms_singleton;
		}

		static void instanceDestroy() {
			if (ms_singleton) {
				delete ms_singleton;
				ms_singleton = nullptr;
			}
		}
	};

	template<typename T> T* singleton<T>::ms_singleton = nullptr;
}


#endif	/* SINGLETON_HPP */

