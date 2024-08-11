#pragma once

#include <iostream>
#include "MyHashTable.hpp"
// �ù�ϣ��ʵ�֣�ֱ�ӵ��ö�Ӧ�ķ������ɣ���set���[]
template <typename K, typename V>
class MyUnorderedMap {
private:
	MyHashTable<K, V> hashtable;
public:
	MyUnorderedMap() : hashtable() {};
	~MyUnorderedMap() {}; // UMap����ʱ�����Զ�����HashTable��������

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