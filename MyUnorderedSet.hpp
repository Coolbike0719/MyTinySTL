#pragma once

#include <iostream>
#include "MyHashTable.hpp"
// �ù�ϣ��ʵ�֣�ֱ�ӵ��ö�Ӧ�ķ�������
template <typename V>
class MyUnorderedSet {
private:
	MyHashTable<V, V> hashtable;
public:
	MyUnorderedSet() : hashtable() {};
	~MyUnorderedSet() {}; // USet����ʱ�����Զ�����HashTable��������

	bool empty() const { return hashtable.getSize() == 0; }

	size_t size() const { return hashtable.getSize(); }

	void clear() { hashtable.clear(); }

	void insert(V value) { hashtable.insert(value, value); }

	void erase(V value) { hashtable.erase(value); }

	bool find(const V& value) { return hashtable.find(value) != nullptr; }
};