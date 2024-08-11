#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include <functional> // for std::hash

template <typename K, typename V>
class MyHashTable {
private:
	// ÿ��Ͱ�еĽ��
	class Node {
	public:
		K key;
		V value;
		Node(const K& key,const V& value) : key(key), value(value) {}
	};

	std::vector<std::list<Node>> table; // ��ϣ��ʹ�ÿ����������ͻ��������ÿ��������Ϊһ��Ͱ
	size_t size;	 // ��ϣ����Ԫ������
	size_t capacity = 10; // ��ʼ��Ĭ������������ʼͰ������,table.size()
	const float loadFactor = 0.75; // ��������ӹ̶�Ϊ0.75
	size_t hash(const K& key) const; // ��ϣ����
	// ���ݣ�����ϣ��Ԫ������/�����������������ʱ����
	void rehash();

public:
	MyHashTable(size_t capacity = 10);
	~MyHashTable();

	// ���Ĺ���
	void insert(const K& key, const V& value);
	bool erase(const K& key);
	V* find(const K& key);
	const V* find(const K& key) const;
	size_t getSize() const;
	void clear() ;

	void print() const;
};

// ���캯��
template <typename K, typename V>
MyHashTable<K, V>::MyHashTable(size_t cap) : table(cap), size(0), capacity(cap){
}

template <typename K, typename V>
MyHashTable<K, V>::~MyHashTable() {
	clear();
}

/* ��ϣ������std::hash�Ǳ�׼�����ģ���࣬������()���Դ���ָ�����͵�key����
	��ϣӳ�䣬�����Ⱦ�������ʵ�ָ������͵�hash���Զ����������û��ṩhash���� */
template<typename K, typename V>
size_t MyHashTable<K, V>::hash(const K& key) const {
	return std::hash<K>()(key) % capacity;
}

// ��ϣ������
template<typename K, typename V>
void MyHashTable<K, V>::rehash() {
	std::vector<std::list<Node>> newTable(table.size() << 1);
	for (auto& bucket : table) {
		for (auto& node : bucket) {
			size_t newIndex = std::hash<K>()(node.key) % newTable.size();
			newTable[newIndex].emplace_back(node.key, node.value);
		}
	}
	table = std::move(newTable);
	capacity = table.size();
}

// �����ֵ��
template<typename K, typename V>
void MyHashTable<K, V>::insert(const K& key, const V& value) {
	if ((float)size / table.size() > loadFactor) {
		rehash();
	}
	size_t index = hash(key); // �Ҹ�keyӳ�䵽�ĸ�Ͱ
	for (auto& node : table[index]) { // �����Ͱ�����ĸ�����key���ڸ�key
		if (node.key == key) {
			node.value = value;
			return;
		}
	}
	// û�ҵ��������Ͱ��Ӹ��µĽ��
	table[index].emplace_back(key, value);

	++size;
}

// ɾ����ֵ��
template<typename K, typename V>
bool MyHashTable<K, V>::erase(const K& key) {
	size_t index = hash(key);
	for (auto it=table[index].begin();it!=table[index].end();++it) { // �����Ͱ�����ĸ�����key���ڸ�key
		if (it->key == key) {
			table[index].erase(it); // Ҫ����list��erase�����봫��ר��������
			--size;
			return true;
		}
	}
	return false;
}

// ����ָ������ֵ������ָ�룬�����Ϳɷ���nullptr��ʾδ���ҵ�����Ȼ����Ҳ����ͨ���׳��쳣���ֵ���ص���������
template<typename K, typename V>
V* MyHashTable<K, V>::find(const K& key) {
	size_t index = hash(key);
	for (auto& node : table[index]) {
		if (node.key == key) {
			return &node.value;
		}
	}
	return nullptr;
}
template<typename K, typename V>
const V* MyHashTable<K, V>::find(const K& key) const {
	size_t index = hash(key);
	for (auto& node : table[index]) {
		if (node.key == key) {
			return &node.value;
		}
	}
	return nullptr;
}

// ��ȡ��ϣ����Ԫ������
template<typename K, typename V>
size_t MyHashTable<K, V>::getSize() const { return size; }

// ��չ�ϣ��
template<typename K, typename V>
void MyHashTable<K, V>::clear() {
	table.clear();
	size = 0;
}

// ��ӡ��ϣ����Ԫ��
template<typename K, typename V>
void MyHashTable<K, V>::print() const {
	for (auto& bucket : table) {
		for (auto& node : bucket) {
			std::cout << node.key << ":" << node.value << " ";
		}
	}
	std::cout << std::endl;
}