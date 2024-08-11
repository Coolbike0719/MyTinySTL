#include <iostream>
#include "MyPriorityQueue.hpp"

int main13() {
	// ʹ�� std::vector ��Ϊ�ײ�����
	MyPriorityQueue<int, std::vector<int>> myPriorityQueue;

	int N;
	std::cin >> N;
	getchar();

	std::string line;
	for (int i = 0; i < N; i++) {
		std::getline(std::cin, line);
		std::istringstream iss(line);
		std::string command;
		iss >> command;

		int element;

		if (command == "push") {
			iss >> element;
			myPriorityQueue.push(element);
		}

		if (command == "pop") {
			try {
				myPriorityQueue.pop();
			}
			catch (const std::runtime_error& e) {
				// �����κδ���
				continue;
			}
		}

		if (command == "top") {
			try {
				std::cout << myPriorityQueue.top() << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cout << "null" << std::endl;
			}
		}

		if (command == "size") {
			std::cout << myPriorityQueue.size() << std::endl;
		}

		if (command == "empty") {
			std::cout << (myPriorityQueue.empty() ? "true" : "false") << std::endl;
		}
	}
	return 0;
}