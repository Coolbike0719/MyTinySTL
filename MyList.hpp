#pragma once

#include <iostream>
#include <stdexcept> // std::out_of_range

template <typename T>
class MyList {
private:
	// 定义结点
	struct Node {
		T data;
		Node* next;
		Node* prev;

		Node(const T& value, Node* nextNode = nullptr, Node* prevNode = nullptr)
			: data(value), next(nextNode), prev(prevNode){
		}
	};

	Node* head;
	Node* tail; // head与tail不是哑结点。当链表为空或只有一个结点时，两者都指向空或唯一结点
	size_t size;

public:
	// 重载<<允许打印链表对象到输出流
	template <typename L>
	friend std::ostream& operator<<(std::ostream& os, const MyList<L>& pt);

	// 构造、析构函数
	MyList();
	~MyList();

	size_t getSize() const;
	void push_back(const T& value);
	void push_front(const T& value);
	void pop_back();
	void pop_front();
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	Node* getNode(const T& value);
	T* find(const T& value);
	void remove(const T& value);
	bool empty() const;
	void clear();


	// 迭代器
	Node* begin();
	Node* end();
	const Node* begin() const;
	const Node* end() const;

	void printElements() const;
};

// 重载 << 运算符，允许打印链表对象到输出流，std::cout<<mylist;
template <typename T>
std::ostream& operator<<(std::ostream& os, const MyList<T>& pt) {
	for (typename MyList<T>::Node* current = pt.head; current;
		current = current->next) {
		os << current->data << " ";
	}
	os << std::endl;
	return os;
}

// 构造函数
template <typename T>
MyList<T>::MyList() : head(nullptr), tail(nullptr), size(0){
}

// 析构函数
template <typename T>
MyList<T>::~MyList() { clear();}

// 获取链表结点数量
template <typename T>
size_t MyList<T>::getSize() const{ return size;}

// 尾部添加元素
template <typename T>
void MyList<T>::push_back(const T& value) {
	Node* newNode = new Node(value, nullptr, tail);

	if (tail) { // 链表非空，正常流程
		tail->next = newNode;
	}
	else { // 链表为空，头结点也要变成该新结点
		head = newNode;
	}
	tail = newNode; // 无论如何尾结点都变成该新结点
	++size;
}

// 头部添加元素
template <typename T>
void MyList<T>::push_front(const T& value) {
	Node* newNode = new Node(value, head, nullptr);

	if (head) { // 链表非空，正常流程
		head->prev = newNode;
	}
	else { // 链表为空，尾结点也要变成该新结点
		tail = newNode;
	}
	head = newNode; // 无论如何头结点都变成该新结点
	++size;
}

// 尾部删除元素
template <typename T>
void MyList<T>::pop_back() {
	if (size > 0) { // 链表非空才进行删除
		Node* newTail = tail->prev; // 取上一个结点作为之后的新尾结点
		delete tail; // 不能delete newTail，因为若链表只有一个结点，newTail为空
		tail = newTail;
		if (tail) {
			tail->next = nullptr;
		}
		else { // 说明删除的是最后一个结点，头指针也要置空
			head = nullptr;
		}
		--size;
	}
}

// 头部删除元素
template <typename T>
void MyList<T>::pop_front() {
	if (size > 0) { // 链表非空才进行删除
		Node* newHead = head->prev; // 取上一个结点作为之后的新头结点
		delete head; // 不能delete newHead，因为若链表只有一个结点，newHead为空
		head = newHead;
		if (head) {
			head->next = nullptr;
		}
		else { // 说明删除的是最后一个结点，尾指针也要置空
			tail = nullptr;
		}
		--size;
	}
}

// []运算符，随机访问元素
template <typename T>
T& MyList<T>::operator[](size_t index) {
	if (index < 0 || index >= size) {
		throw std::out_of_range("Index out of range");
	}
	Node* curr = head;
	for (size_t i = 0; i < index; ++i) {
		curr = curr->next;
	}
	return curr->data;
}
template <typename T>
const T& MyList<T>::operator[](size_t index) const {
	if (index < 0 || index >= size) {
		throw std::out_of_range("Index out of range");
	}
	Node* curr = head;
	for (size_t i = 0; i < index; ++i) {
		curr = curr->next;
	}
	return curr->data;
}

// 获取指定值的结点
template <typename T>
typename MyList<T>::Node* MyList<T>::getNode(const T& value) {
	Node* node = head;
	while (node && node->value != value) {
		node = node->next;
	}
	return node;
}

//  获取指定值的指针(迭代器)，这样可以返回nullptr表示查找失败，如果返回是值会有歧义，也可抛出异常解决
template <typename T>
T* MyList<T>::find(const T& value) {
	Node* node = getNode(value);
	if (node == nullptr) {
		return nullptr;
	}
	return &node->val;
}

// 删除指定值的结点
template <typename T>
void MyList<T>::remove(const T& value) {
	Node* node = head;
	while (node && node->data != value) {
		node = node->next;
	}
	if (node == nullptr) { return;}

	if (node != head && node !=tail) {		 // 如果不是头尾结点，正常删除
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	else if (node == head && node == tail) { // 如果同时是头尾结点，删除后链表为空
		head = tail = nullptr;
	}
	else if (node == head) { // 只是头结点，更新头结点
		head = node->next;
		head->prev = nullptr;
	}
	else {					// 只是尾结点，更新尾结点
		tail = node->prev;
		tail->next = nullptr;
	}
	--size;
	delete node;
	node = nullptr;
}

template <typename T>
bool MyList<T>::empty() const{ return size == 0; }

// 清空链表
template <typename T>
void MyList<T>::clear() {
	while (head) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	tail = nullptr;
	size = 0;
}

// 起始迭代器
template <typename T>
typename MyList<T>::Node* MyList<T>::begin() { return head; }
template <typename T>
const typename MyList<T>::Node* MyList<T>::begin() const { return head; }

// 末尾迭代器
template <typename T>
typename MyList<T>::Node* MyList<T>::end() { return nullptr; }
template <typename T>
const typename MyList<T>::Node* MyList<T>::end() const { return nullptr; }

// 打印链表
template <typename T>
void MyList<T>::printElements() const{
	for (Node* curr = head; curr; curr = curr->next) {
		std::cout << curr->data << " ";
	}
	std::cout << std::endl;
}