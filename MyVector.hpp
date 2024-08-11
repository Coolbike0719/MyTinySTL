#pragma once

#include <iostream>
#include <cstddef> // size_t，好像默认也有
#include <algorithm> // std::copy
#include <stdexcept> // std::out_of_range

template<typename T>
class MyVector {
private:
    T* elements;
    size_t capacity;
	size_t size;

public:
    // 构造、析构函数
    MyVector();
    MyVector(size_t n);
    MyVector(const MyVector& other);
    ~MyVector();

    // 赋值运算符重载
    MyVector<T>& operator=(const MyVector<T>& other);

    // 核心功能
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t getSize() const;
    size_t getCapacity() const;
    void push_back(const T& value);
    void insert(size_t index, const T& value);
    void pop_back();
    void clear();

    // 迭代器功能
    T* begin();
    const T* begin() const;
    T* end();
    const T* end() const;

    void printElements() const;
    void reserve(size_t newCapacity); // 数组扩容

};


// 默认构造函数
template<typename T>
MyVector<T>::MyVector() : elements(nullptr), capacity(0), size(0) {}

// 有参构造函数
template<typename T>
MyVector<T>::MyVector(size_t n) : capacity(n), size(n) {
	elements = new T[capacity];
}

// 拷贝构造函数
template<typename T>
MyVector<T>::MyVector(const MyVector<T>& other) : capacity(other.capacity), size(other.size) {
	elements = new T[capacity];
	std::copy(other.elements, other.elements + size, elements);
}

// 析构函数
template<typename T>
MyVector<T>::~MyVector() { delete[] elements; };

// 赋值运算符
template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other) {
	if (this != &other) // 传入的右值是对象变量，检查其地址是否与当前对象地址相同
	{
		delete[] elements; // 把当前的释放
		capacity = other.capacity;
		size = other.size;
		elements = new T[capacity];
		std::copy(other.elements, other.elements + size, elements); // 把other的元素拷贝过来
	}
	return *this;
}

// []运算符，随机访问元素
template<typename T>
T& MyVector<T>::operator[](size_t index) {
	if (index >= size) {
		throw std::out_of_range("Index out of range");
	}
	return elements[index];
}
template<typename T>
const T& MyVector<T>::operator[] (size_t index) const {
	if (index >= size) {
		throw std::out_of_range("Index out of range");
	}
	return elements[index];
}

// 获取大小
template<typename T>
size_t MyVector<T>::getSize() const { return size; }

// 获取容量
template<typename T>
size_t MyVector<T>::getCapacity() const { return capacity; }

// 尾部添加元素
template<typename T>
void MyVector<T>::push_back(const T& value) {
	if (size >= capacity) {
		reserve(capacity == 0 ? 1 : capacity << 1); //如果容量是0就扩为1，否则两倍
	}
	elements[size++] = value;
}

// 随机位置插入元素,其后元素集体后移一步
template<typename T>
void MyVector<T>::insert(size_t index, const T& value) {
	if (index > size) {
		throw std::out_of_range("Index out of range");
	}
	if (size >= capacity) {
		reserve(capacity == 0 ? 1 : capacity << 1);
	}
	for (size_t i = size; i > index; --i) {
		elements[i] = elements[i - 1];
	}
	elements[index] = value;
	++size;
}

// 尾部删除元素
template<typename T>
void MyVector<T>::pop_back() {
	if (size > 0) {
		--size;
	}
}

// 清空数组
template<typename T>
void MyVector<T>::clear() { size = 0; }

// 数组起始位置迭代器
template<typename T>
T* MyVector<T>::begin() { return elements; }
template<typename T>
const T* MyVector<T>::begin() const { return elements; }

// 数组结束位置迭代器
template<typename T>
T* MyVector<T>::end() { return elements + size; }
template<typename T>
const T* MyVector<T>::end() const { return elements + size; }

// 打印数组元素
template<typename T>
void MyVector<T>::printElements() const {
	for (size_t i = 0; i < size; ++i) {
		std::cout << elements[i] <<" ";
	}
	std::cout << std::endl;
}

// 数组扩容
template<typename T>
void MyVector<T>::reserve(size_t newCapacity) {
	if (newCapacity > capacity) {
		T* newElements = new T[newCapacity];
		std::copy(elements, elements + size, newElements);
		delete[] elements;
		elements = newElements;
		capacity = newCapacity;
	}
}