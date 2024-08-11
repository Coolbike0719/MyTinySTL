#pragma once

#include <iostream>
#include "MyHashTable.hpp"
// 用哈希表实现，直接调用对应的方法即可，比set多个[]
template <typename K, typename V>
class MyUnorderedMap {
private:
	MyHashTable<K, V> hashtable;
public:
	MyUnorderedMap() : hashtable() {};
	~MyUnorderedMap() {}; // UMap销毁时会先自动调用HashTable的析构的

	bool empty() const { return hashtable.getSize() == 0; }

	size_t size() const { return hashtable.getSize(); }

	void clear() { hashtable.clear(); }

	void insert(K key, K value) { hashtable.insert(key, value); }

	void erase(K key) { hashtable.erase(key); }

	bool find(const K& key) { return hashtable.find(key) != nullptr; }

	V& operator[](const K& key) {
		V* node = hashtable.find(key);
		if (node == nullptr) {
			hashtable.insert(key, V());
			node = hashtable.find(key);
		}
		return *node;
	}
};