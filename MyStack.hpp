#include <iostream>
#include <vector>
#include <list>
#include <deque>

template<typename T, typename Container = std::deque<T>>
class MyStack {
private:
	Container data; // 存储栈元素的底层容器

public:
	// 构造、析构函数默认即可，因为实际操作的是底层容器

	// 核心功能
	void push(const T& value);
	void pop();
	T& top();
	bool empty() const;
	size_t size() const;

};

// 压入元素到栈顶
template<typename T, typename Container>
void MyStack<T, Container>::push(const T& value) {
	data.push_back(value);
}

// 弹出栈顶元素
template<typename T, typename Container>
void MyStack<T, Container>::pop() {
	if (!empty()) {
		data.pop_back();
	}
	else {
		throw std::runtime_error("Stack is empty.");
	}
}

// 返回栈顶元素的引用
template<typename T, typename Container>
T& MyStack<T, Container>::top() {
	if (!empty()) {
		return data.back();
	}
	else {
		throw std::runtime_error("Stack is empty.");
	}
}

// 检查栈是否为空
template<typename T, typename Container>
bool MyStack<T, Container>::empty() const {
	return data.empty();
}

// 返回栈的大小
template<typename T, typename Container>
size_t MyStack<T, Container>::size() const {
	return data.size();
}
