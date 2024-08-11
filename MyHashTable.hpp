#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include <functional> // for std::hash

template <typename K, typename V>
class MyHashTable {
private:
	// 每个桶中的结点
	class Node {
	public:
		K key;
		V value;
		Node(const K& key,const V& value) : key(key), value(value) {}
	};

	std::vector<std::list<Node>> table; // 哈希表，使用开链法处理冲突，数组中每个链表作为一个桶
	size_t size;	 // 哈希表内元素数量
	size_t capacity = 10; // 初始表默认容量，即初始桶的数量,table.size()
	const float loadFactor = 0.75; // 最大负载因子固定为0.75
	size_t hash(const K& key) const; // 哈希函数
	// 扩容，当哈希表元素数量/容量超过最大负载因子时触发
	void rehash();

public:
	MyHashTable(size_t capacity = 10);
	~MyHashTable();

	// 核心功能
	void insert(const K& key, const V& value);
	bool erase(const K& key);
	V* find(const K& key);
	const V* find(const K& key) const;
	size_t getSize() const;
	void clear() ;

	void print() const;
};

// 构造函数
template <typename K, typename V>
MyHashTable<K, V>::MyHashTable(size_t cap) : table(cap), size(0), capacity(cap){
}

template <typename K, typename V>
MyHashTable<K, V>::~MyHashTable() {
	clear();
}

/* 哈希函数，std::hash是标准库里的模板类，重载了()可以传入指定类型的key进行
	哈希映射，我们先经过它以实现更多类型的hash，自定义类型需用户提供hash函数 */
template<typename K, typename V>
size_t MyHashTable<K, V>::hash(const K& key) const {
	return std::hash<K>()(key) % capacity;
}

// 哈希表扩容
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

// 插入键值对
template<typename K, typename V>
void MyHashTable<K, V>::insert(const K& key, const V& value) {
	if ((float)size / table.size() > loadFactor) {
		rehash();
	}
	size_t index = hash(key); // 找该key映射到哪个桶
	for (auto& node : table[index]) { // 在这个桶里找哪个结点的key等于该key
		if (node.key == key) {
			node.value = value;
			return;
		}
	}
	// 没找到就往这个桶里加个新的结点
	table[index].emplace_back(key, value);

	++size;
}

// 删除键值对
template<typename K, typename V>
bool MyHashTable<K, V>::erase(const K& key) {
	size_t index = hash(key);
	for (auto it=table[index].begin();it!=table[index].end();++it) { // 在这个桶里找哪个结点的key等于该key
		if (it->key == key) {
			table[index].erase(it); // 要调用list的erase，必须传入专属迭代器
			--size;
			return true;
		}
	}
	return false;
}

// 查找指定键的值，返回指针，这样就可返回nullptr表示未查找到。当然这种也可以通过抛出异常解决值返回的歧义问题
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

// 获取哈希表中元素数量
template<typename K, typename V>
size_t MyHashTable<K, V>::getSize() const { return size; }

// 清空哈希表
template<typename K, typename V>
void MyHashTable<K, V>::clear() {
	table.clear();
	size = 0;
}

// 打印哈希表中元素
template<typename K, typename V>
void MyHashTable<K, V>::print() const {
	for (auto& bucket : table) {
		for (auto& node : bucket) {
			std::cout << node.key << ":" << node.value << " ";
		}
	}
	std::cout << std::endl;
}