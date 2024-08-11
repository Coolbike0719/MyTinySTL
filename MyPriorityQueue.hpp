#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>

template <typename T, typename Container = std::vector<T>>
class MyPriorityQueue {
private:
	Container heap;

	// 从指定结点开始向上堆化，适合插入结点，传入最后一个结点即为插入后的维护
	void heapifyUp(int index) {
		int child = index;
		while (child > 0) {
			int parent = (child - 1) / 2;
			if (heap[child] > heap[parent]) { // 如果插入结点大于当前父结点就继续上移
				std::swap(heap[child], heap[parent]);
				child = parent;
			}
			else break;
		}
	}

	// 下滤堆化，从指定结点开始往下堆化，传入根结点即为自上而下的堆化，适合创建和删除后的维护
	void heapifyDown(int index) {
		int parent = index;
		//int left = index * 2 + 1; // 默认根结点从0开始，即无哨兵结点
		//int right = index * 2 + 2; 
		while (2 * parent + 1 < heap.size()) {
			int child = parent * 2 + 1;
			if (child + 1 < heap.size() && heap[child] < heap[child + 1]) { // 右子结点存在且更大
				++child; // 指向更大的右结点
			}
			if (heap[parent] >= heap[child]) break;// 如果当前结点大于两个子结点，则堆化成功
			std::swap(heap[parent], heap[child]); // 否则当前结点被较大的子结点替代继续下移
			parent = child;
		}
	}


public:
	MyPriorityQueue() {}
	MyPriorityQueue(const Container& c) :heap(c) { // 如果传了一个已有容器，则将堆化
		for (int i = (heap.size())/2; i >= 0; --i) {
			heapifyDown(i);
		}
	}

	void push(const T& value) {
		heap.push_back(value);
		heapifyUp(heap.size() - 1);
	}

	void pop() {
		if (!empty()) {
			std::swap(heap[0], heap[heap.size() - 1]);
			heap.pop_back();
			heapifyDown(0);
		}
		else {
			throw std::runtime_error("Priority queue is empty.");
		}
	}

	T& top() {
		if (!empty()) {
			return heap[0];
		}
		else {
			throw std::runtime_error("Priority queue is empty.");
		}
	}

	bool empty() const {
		return heap.empty();
	}

	size_t size() const {
		return heap.size();
	}
};
