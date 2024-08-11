#include <iostream>
#include <vector>
#include <list>
#include <deque>

template<typename T, typename Container = std::deque<T>>
class MyQueue {
private:
	Container data; // �洢ջԪ�صĵײ�����

public:
	// ���졢��������Ĭ�ϼ��ɣ���Ϊʵ�ʲ������ǵײ�����

	// ���Ĺ���
	void push(const T& value);
	void pop();
	T& front();
	T& back();
	bool empty() const;
	size_t size() const;

};

// ѹ��Ԫ�ص���β
template<typename T, typename Container>
void MyQueue<T, Container>::push(const T& value) {
	data.push_back(value);
}

// ��������Ԫ��
template<typename T, typename Container>
void MyQueue<T, Container>::pop() {
	if (!empty()) {
		data.pop_front();
	}
	else {
		throw std::runtime_error("Queue is empty.");
	}
}

// ���ض���Ԫ�ص�����
template<typename T, typename Container>
T& MyQueue<T, Container>::front() {
	if (!empty()) {
		return data.front();
	}
	else {
		throw std::runtime_error("Queue is empty.");
	}
}

// ���ض�βԪ�ص�����
template<typename T, typename Container>
T& MyQueue<T, Container>::back() {
	if (!empty()) {
		return data.back();
	}
	else {
		throw std::runtime_error("Queue is empty.");
	}
}

// �������Ƿ�Ϊ��
template<typename T, typename Container>
bool MyQueue<T, Container>::empty() const {
	return data.empty();
}

// ���ض��еĴ�С
template<typename T, typename Container>
size_t MyQueue<T, Container>::size() const {
	return data.size();
}
