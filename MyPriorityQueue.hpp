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

	// ��ָ����㿪ʼ���϶ѻ����ʺϲ����㣬�������һ����㼴Ϊ������ά��
	void heapifyUp(int index) {
		int child = index;
		while (child > 0) {
			int parent = (child - 1) / 2;
			if (heap[child] > heap[parent]) { // �����������ڵ�ǰ�����ͼ�������
				std::swap(heap[child], heap[parent]);
				child = parent;
			}
			else break;
		}
	}

	// ���˶ѻ�����ָ����㿪ʼ���¶ѻ����������㼴Ϊ���϶��µĶѻ����ʺϴ�����ɾ�����ά��
	void heapifyDown(int index) {
		int parent = index;
		//int left = index * 2 + 1; // Ĭ�ϸ�����0��ʼ�������ڱ����
		//int right = index * 2 + 2; 
		while (2 * parent + 1 < heap.size()) {
			int child = parent * 2 + 1;
			if (child + 1 < heap.size() && heap[child] < heap[child + 1]) { // ���ӽ������Ҹ���
				++child; // ָ�������ҽ��
			}
			if (heap[parent] >= heap[child]) break;// �����ǰ�����������ӽ�㣬��ѻ��ɹ�
			std::swap(heap[parent], heap[child]); // ����ǰ��㱻�ϴ���ӽ�������������
			parent = child;
		}
	}


public:
	MyPriorityQueue() {}
	MyPriorityQueue(const Container& c) :heap(c) { // �������һ�������������򽫶ѻ�
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
