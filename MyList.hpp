#pragma once

#include <iostream>
#include <stdexcept> // std::out_of_range

template <typename T>
class MyList {
private:
	// ������
	struct Node {
		T data;
		Node* next;
		Node* prev;

		Node(const T& value, Node* nextNode = nullptr, Node* prevNode = nullptr)
			: data(value), next(nextNode), prev(prevNode){
		}
	};

	Node* head;
	Node* tail; // head��tail�����ƽ�㡣������Ϊ�ջ�ֻ��һ�����ʱ�����߶�ָ��ջ�Ψһ���
	size_t size;

public:
	// ����<<�����ӡ������������
	template <typename L>
	friend std::ostream& operator<<(std::ostream& os, const MyList<L>& pt);

	// ���졢��������
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


	// ������
	Node* begin();
	Node* end();
	const Node* begin() const;
	const Node* end() const;

	void printElements() const;
};

// ���� << ������������ӡ��������������std::cout<<mylist;
template <typename T>
std::ostream& operator<<(std::ostream& os, const MyList<T>& pt) {
	for (typename MyList<T>::Node* current = pt.head; current;
		current = current->next) {
		os << current->data << " ";
	}
	os << std::endl;
	return os;
}

// ���캯��
template <typename T>
MyList<T>::MyList() : head(nullptr), tail(nullptr), size(0){
}

// ��������
template <typename T>
MyList<T>::~MyList() { clear();}

// ��ȡ����������
template <typename T>
size_t MyList<T>::getSize() const{ return size;}

// β�����Ԫ��
template <typename T>
void MyList<T>::push_back(const T& value) {
	Node* newNode = new Node(value, nullptr, tail);

	if (tail) { // ����ǿգ���������
		tail->next = newNode;
	}
	else { // ����Ϊ�գ�ͷ���ҲҪ��ɸ��½��
		head = newNode;
	}
	tail = newNode; // �������β��㶼��ɸ��½��
	++size;
}

// ͷ�����Ԫ��
template <typename T>
void MyList<T>::push_front(const T& value) {
	Node* newNode = new Node(value, head, nullptr);

	if (head) { // ����ǿգ���������
		head->prev = newNode;
	}
	else { // ����Ϊ�գ�β���ҲҪ��ɸ��½��
		tail = newNode;
	}
	head = newNode; // �������ͷ��㶼��ɸ��½��
	++size;
}

// β��ɾ��Ԫ��
template <typename T>
void MyList<T>::pop_back() {
	if (size > 0) { // ����ǿղŽ���ɾ��
		Node* newTail = tail->prev; // ȡ��һ�������Ϊ֮�����β���
		delete tail; // ����delete newTail����Ϊ������ֻ��һ����㣬newTailΪ��
		tail = newTail;
		if (tail) {
			tail->next = nullptr;
		}
		else { // ˵��ɾ���������һ����㣬ͷָ��ҲҪ�ÿ�
			head = nullptr;
		}
		--size;
	}
}

// ͷ��ɾ��Ԫ��
template <typename T>
void MyList<T>::pop_front() {
	if (size > 0) { // ����ǿղŽ���ɾ��
		Node* newHead = head->prev; // ȡ��һ�������Ϊ֮�����ͷ���
		delete head; // ����delete newHead����Ϊ������ֻ��һ����㣬newHeadΪ��
		head = newHead;
		if (head) {
			head->next = nullptr;
		}
		else { // ˵��ɾ���������һ����㣬βָ��ҲҪ�ÿ�
			tail = nullptr;
		}
		--size;
	}
}

// []��������������Ԫ��
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

// ��ȡָ��ֵ�Ľ��
template <typename T>
typename MyList<T>::Node* MyList<T>::getNode(const T& value) {
	Node* node = head;
	while (node && node->value != value) {
		node = node->next;
	}
	return node;
}

//  ��ȡָ��ֵ��ָ��(������)���������Է���nullptr��ʾ����ʧ�ܣ����������ֵ�������壬Ҳ���׳��쳣���
template <typename T>
T* MyList<T>::find(const T& value) {
	Node* node = getNode(value);
	if (node == nullptr) {
		return nullptr;
	}
	return &node->val;
}

// ɾ��ָ��ֵ�Ľ��
template <typename T>
void MyList<T>::remove(const T& value) {
	Node* node = head;
	while (node && node->data != value) {
		node = node->next;
	}
	if (node == nullptr) { return;}

	if (node != head && node !=tail) {		 // �������ͷβ��㣬����ɾ��
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	else if (node == head && node == tail) { // ���ͬʱ��ͷβ��㣬ɾ��������Ϊ��
		head = tail = nullptr;
	}
	else if (node == head) { // ֻ��ͷ��㣬����ͷ���
		head = node->next;
		head->prev = nullptr;
	}
	else {					// ֻ��β��㣬����β���
		tail = node->prev;
		tail->next = nullptr;
	}
	--size;
	delete node;
	node = nullptr;
}

template <typename T>
bool MyList<T>::empty() const{ return size == 0; }

// �������
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

// ��ʼ������
template <typename T>
typename MyList<T>::Node* MyList<T>::begin() { return head; }
template <typename T>
const typename MyList<T>::Node* MyList<T>::begin() const { return head; }

// ĩβ������
template <typename T>
typename MyList<T>::Node* MyList<T>::end() { return nullptr; }
template <typename T>
const typename MyList<T>::Node* MyList<T>::end() const { return nullptr; }

// ��ӡ����
template <typename T>
void MyList<T>::printElements() const{
	for (Node* curr = head; curr; curr = curr->next) {
		std::cout << curr->data << " ";
	}
	std::cout << std::endl;
}