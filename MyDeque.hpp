#pragma once

#include <iostream>
#include <stdexcept>

template <typename T>
class MyDeque {
private:
	T* elements;	// 用一个循环数组简易模拟deque，容量不足时扩充该数组，而非创建更多数组
	size_t size;
	size_t capacity;
	size_t frontIndex;	// deque(循环数组)的前端索引，指向首元素
	size_t backIndex;	// deque(循环数组)的后端索引，指向空位置

	// 内部数组扩容,由于只有一个数组，扩容要复制旧数组过去
	void resize();
public:
	// 构造、析构函数
	MyDeque();
	~MyDeque();

	// 核心功能
	void push_back(const T& value);
	void push_front(const T& value);
	void pop_back();
	void pop_front();
	size_t getSize() const;
	void clear();

	// 重载[]提供索引访问
	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	// 打印元素
	void printElements() const;
};

// 构造、析构函数
template <typename T>
MyDeque<T>::MyDeque() : elements(nullptr), size(0), capacity(0),frontIndex(0),backIndex(0) {
}

template <typename T>
MyDeque<T>::~MyDeque() {
	clear();
	delete[] elements;
}

// 内部数组扩容，当size==capacity时又添加新元素触发
template <typename T>
void MyDeque<T>::resize() {
	// 找块两倍大的新空间
	size_t newCapacity = (capacity == 0) ? 1 : capacity << 1;
	T* newElements = new T[newCapacity];

	// 复制旧数组，注意由于是循环数组，旧数组首元素不一定从0开始，且会循环到前端
	for (size_t i = 0; i < size; ++i) {
		newElements[i] = elements[frontIndex];
		frontIndex = (frontIndex + 1) % capacity;
	}
	frontIndex = 0;
	backIndex = size;
	delete[] elements;
	elements = newElements;
	capacity = newCapacity;
}

// 后端添加元素
template <typename T>
void MyDeque<T>::push_back(const T& value) {
	if (size == capacity) {
		resize();
	}

	elements[backIndex] = value;
	backIndex = (backIndex + 1) % capacity;
	++size;
}

// 前端添加元素
template <typename T>
void MyDeque<T>::push_front(const T& value) {
	if (size == capacity) {
		resize();
	}

	frontIndex = (frontIndex - 1) % capacity;
	elements[frontIndex] = value;
	++size;
}

// 后端删除元素
template <typename T>
void MyDeque<T>::pop_back() {
	if (size == 0) {
		throw std::out_of_range("Deque is empty");
	}
	backIndex = (backIndex - 1) % capacity;
	--size;
}

// 前端删除元素
template <typename T>
void MyDeque<T>::pop_front() {
	if (size == 0) {
		throw std::out_of_range("Deque is empty");
	}
	frontIndex = (frontIndex + 1) % capacity;
	--size;
}

// 获取Deque中元素数量
template <typename T>
size_t MyDeque<T>::getSize() const { return size; }

// 清空元素，循环数组无需重置前后端索引
template <typename T>
void MyDeque<T>::clear() {
	while (size > 0) {
		pop_front();
	}
}

// 获取指定索引的元素，注意循环数组是内部实现，对外下标依然要表现为从0到size-1
template <typename T>
T& MyDeque<T>::operator[](size_t index) {
	if (index < 0 || index >= size) {
		throw std::out_of_range("Index out of range");
	}
	return elements[(frontIndex + index) % capacity]; // 对外frontIndex表现为0号元素
}
template <typename T>
const T& MyDeque<T>::operator[](size_t index) const {
	if (index < 0 || index >= size) {
		throw std::out_of_range("Index out of range");
	}
	return elements[(frontIndex + index) % capacity];
}

// 打印元素，同样应该从frontIndex开始打印
template <typename T>
void MyDeque<T>::printElements() const {
	for (size_t i = 0; i < size; ++i) {
		std::cout << elements[(frontIndex + i) % capacity] << " ";
	}
	std::cout << std::endl;
}