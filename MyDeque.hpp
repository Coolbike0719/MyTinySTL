#pragma once

#include <iostream>
#include <stdexcept>

template <typename T>
class MyDeque {
private:
	T* elements;	// ��һ��ѭ���������ģ��deque����������ʱ��������飬���Ǵ�����������
	size_t size;
	size_t capacity;
	size_t frontIndex;	// deque(ѭ������)��ǰ��������ָ����Ԫ��
	size_t backIndex;	// deque(ѭ������)�ĺ��������ָ���λ��

	// �ڲ���������,����ֻ��һ�����飬����Ҫ���ƾ������ȥ
	void resize();
public:
	// ���졢��������
	MyDeque();
	~MyDeque();

	// ���Ĺ���
	void push_back(const T& value);
	void push_front(const T& value);
	void pop_back();
	void pop_front();
	size_t getSize() const;
	void clear();

	// ����[]�ṩ��������
	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	// ��ӡԪ��
	void printElements() const;
};

// ���졢��������
template <typename T>
MyDeque<T>::MyDeque() : elements(nullptr), size(0), capacity(0),frontIndex(0),backIndex(0) {
}

template <typename T>
MyDeque<T>::~MyDeque() {
	clear();
	delete[] elements;
}

// �ڲ��������ݣ���size==capacityʱ�������Ԫ�ش���
template <typename T>
void MyDeque<T>::resize() {
	// �ҿ���������¿ռ�
	size_t newCapacity = (capacity == 0) ? 1 : capacity << 1;
	T* newElements = new T[newCapacity];

	// ���ƾ����飬ע��������ѭ�����飬��������Ԫ�ز�һ����0��ʼ���һ�ѭ����ǰ��
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

// ������Ԫ��
template <typename T>
void MyDeque<T>::push_back(const T& value) {
	if (size == capacity) {
		resize();
	}

	elements[backIndex] = value;
	backIndex = (backIndex + 1) % capacity;
	++size;
}

// ǰ�����Ԫ��
template <typename T>
void MyDeque<T>::push_front(const T& value) {
	if (size == capacity) {
		resize();
	}

	frontIndex = (frontIndex - 1) % capacity;
	elements[frontIndex] = value;
	++size;
}

// ���ɾ��Ԫ��
template <typename T>
void MyDeque<T>::pop_back() {
	if (size == 0) {
		throw std::out_of_range("Deque is empty");
	}
	backIndex = (backIndex - 1) % capacity;
	--size;
}

// ǰ��ɾ��Ԫ��
template <typename T>
void MyDeque<T>::pop_front() {
	if (size == 0) {
		throw std::out_of_range("Deque is empty");
	}
	frontIndex = (frontIndex + 1) % capacity;
	--size;
}

// ��ȡDeque��Ԫ������
template <typename T>
size_t MyDeque<T>::getSize() const { return size; }

// ���Ԫ�أ�ѭ��������������ǰ�������
template <typename T>
void MyDeque<T>::clear() {
	while (size > 0) {
		pop_front();
	}
}

// ��ȡָ��������Ԫ�أ�ע��ѭ���������ڲ�ʵ�֣������±���ȻҪ����Ϊ��0��size-1
template <typename T>
T& MyDeque<T>::operator[](size_t index) {
	if (index < 0 || index >= size) {
		throw std::out_of_range("Index out of range");
	}
	return elements[(frontIndex + index) % capacity]; // ����frontIndex����Ϊ0��Ԫ��
}
template <typename T>
const T& MyDeque<T>::operator[](size_t index) const {
	if (index < 0 || index >= size) {
		throw std::out_of_range("Index out of range");
	}
	return elements[(frontIndex + index) % capacity];
}

// ��ӡԪ�أ�ͬ��Ӧ�ô�frontIndex��ʼ��ӡ
template <typename T>
void MyDeque<T>::printElements() const {
	for (size_t i = 0; i < size; ++i) {
		std::cout << elements[(frontIndex + i) % capacity] << " ";
	}
	std::cout << std::endl;
}