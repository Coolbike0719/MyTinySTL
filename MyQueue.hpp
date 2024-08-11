#include <iostream>
#include <vector>
#include <list>
#include <deque>

template<typename T, typename Container = std::deque<T>>
class MyQueue {
private:
	Container data; // 存储栈元素的底层容器

public:
	// 构造、析构函数默认即可，因为实际操作的是底层容器

	// 核心功能
	void push(const T& value);
	void pop();
	T& front();
	T& back();
	bool empty() const;
	size_t size() const;

};

// 压入元素到队尾
template<typename T, typename Container>
void MyQueue<T, Container>::push(const T& value) {
	data.push_back(value);
}

// 弹出队首元素
template<typename T, typename Container>
void MyQueue<T, Container>::pop() {
	if (!empty()) {
		data.pop_front();
	}
	else {
		throw std::runtime_error("Queue is empty.");
	}
}

// 返回队首元素的引用
template<typename T, typename Container>
T& MyQueue<T, Container>::front() {
	if (!empty()) {
		return data.front();
	}
	else {
		throw std::runtime_error("Queue is empty.");
	}
}

// 返回队尾元素的引用
template<typename T, typename Container>
T& MyQueue<T, Container>::back() {
	if (!empty()) {
		return data.back();
	}
	else {
		throw std::runtime_error("Queue is empty.");
	}
}

// 检查队列是否为空
template<typename T, typename Container>
bool MyQueue<T, Container>::empty() const {
	return data.empty();
}

// 返回队列的大小
template<typename T, typename Container>
size_t MyQueue<T, Container>::size() const {
	return data.size();
}
