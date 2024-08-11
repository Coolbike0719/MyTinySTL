#pragma once

#include <iostream>
#include <cstddef> // size_t������Ĭ��Ҳ��
#include <algorithm> // std::copy
#include <stdexcept> // std::out_of_range

template<typename T>
class MyVector {
private:
    T* elements;
    size_t capacity;
	size_t size;

public:
    // ���졢��������
    MyVector();
    MyVector(size_t n);
    MyVector(const MyVector& other);
    ~MyVector();

    // ��ֵ���������
    MyVector<T>& operator=(const MyVector<T>& other);

    // ���Ĺ���
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t getSize() const;
    size_t getCapacity() const;
    void push_back(const T& value);
    void insert(size_t index, const T& value);
    void pop_back();
    void clear();

    // ����������
    T* begin();
    const T* begin() const;
    T* end();
    const T* end() const;

    void printElements() const;
    void reserve(size_t newCapacity); // ��������

};


// Ĭ�Ϲ��캯��
template<typename T>
MyVector<T>::MyVector() : elements(nullptr), capacity(0), size(0) {}

// �вι��캯��
template<typename T>
MyVector<T>::MyVector(size_t n) : capacity(n), size(n) {
	elements = new T[capacity];
}

// �������캯��
template<typename T>
MyVector<T>::MyVector(const MyVector<T>& other) : capacity(other.capacity), size(other.size) {
	elements = new T[capacity];
	std::copy(other.elements, other.elements + size, elements);
}

// ��������
template<typename T>
MyVector<T>::~MyVector() { delete[] elements; };

// ��ֵ�����
template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other) {
	if (this != &other) // �������ֵ�Ƕ��������������ַ�Ƿ��뵱ǰ�����ַ��ͬ
	{
		delete[] elements; // �ѵ�ǰ���ͷ�
		capacity = other.capacity;
		size = other.size;
		elements = new T[capacity];
		std::copy(other.elements, other.elements + size, elements); // ��other��Ԫ�ؿ�������
	}
	return *this;
}

// []��������������Ԫ��
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

// ��ȡ��С
template<typename T>
size_t MyVector<T>::getSize() const { return size; }

// ��ȡ����
template<typename T>
size_t MyVector<T>::getCapacity() const { return capacity; }

// β�����Ԫ��
template<typename T>
void MyVector<T>::push_back(const T& value) {
	if (size >= capacity) {
		reserve(capacity == 0 ? 1 : capacity << 1); //���������0����Ϊ1����������
	}
	elements[size++] = value;
}

// ���λ�ò���Ԫ��,���Ԫ�ؼ������һ��
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

// β��ɾ��Ԫ��
template<typename T>
void MyVector<T>::pop_back() {
	if (size > 0) {
		--size;
	}
}

// �������
template<typename T>
void MyVector<T>::clear() { size = 0; }

// ������ʼλ�õ�����
template<typename T>
T* MyVector<T>::begin() { return elements; }
template<typename T>
const T* MyVector<T>::begin() const { return elements; }

// �������λ�õ�����
template<typename T>
T* MyVector<T>::end() { return elements + size; }
template<typename T>
const T* MyVector<T>::end() const { return elements + size; }

// ��ӡ����Ԫ��
template<typename T>
void MyVector<T>::printElements() const {
	for (size_t i = 0; i < size; ++i) {
		std::cout << elements[i] <<" ";
	}
	std::cout << std::endl;
}

// ��������
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