#include <iostream>
#include <vector>
#include <list>
#include <deque>

template<typename T, typename Container = std::deque<T>>
class MyStack {
private:
	Container data; // �洢ջԪ�صĵײ�����

public:
	// ���졢��������Ĭ�ϼ��ɣ���Ϊʵ�ʲ������ǵײ�����

	// ���Ĺ���
	void push(const T& value);
	void pop();
	T& top();
	bool empty() const;
	size_t size() const;

};

// ѹ��Ԫ�ص�ջ��
template<typename T, typename Container>
void MyStack<T, Container>::push(const T& value) {
	data.push_back(value);
}

// ����ջ��Ԫ��
template<typename T, typename Container>
void MyStack<T, Container>::pop() {
	if (!empty()) {
		data.pop_back();
	}
	else {
		throw std::runtime_error("Stack is empty.");
	}
}

// ����ջ��Ԫ�ص�����
template<typename T, typename Container>
T& MyStack<T, Container>::top() {
	if (!empty()) {
		return data.back();
	}
	else {
		throw std::runtime_error("Stack is empty.");
	}
}

// ���ջ�Ƿ�Ϊ��
template<typename T, typename Container>
bool MyStack<T, Container>::empty() const {
	return data.empty();
}

// ����ջ�Ĵ�С
template<typename T, typename Container>
size_t MyStack<T, Container>::size() const {
	return data.size();
}
