#pragma once

#include <iostream>
#include "MyHashTable.hpp"
// 用哈希表实现，直接调用对应的方法即可
template <typename V>
class MyUnorderedSet {
private:
	MyHashTable<V, V> hashtable;
public:
	MyUnorderedSet() : hashtable() {};
	~MyUnorderedSet() {}; // USet销毁时会先自动调用HashTable的析构的

	bool empty() const { return hashtable.getSize() == 0; }

	size_t size() const { return hashtable.getSize(); }

	void clear() { hashtable.clear(); }

	void insert(V value) { hashtable.insert(value, value); }

	void erase(V value) { hashtable.erase(value); }

	bool find(const V& value) { return hashtable.find(value) != nullptr; }
};