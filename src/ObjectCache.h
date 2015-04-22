#ifndef __OLL_OBJECTCACHE_H__
#define __OLL_OBJECTCACHE_H__

#include <vector>

template<typename T>
class ObjectCache {
	private std::vector<T> objects;

	void add(T object) {
		objects.push_back(object);
	}
}

#endif