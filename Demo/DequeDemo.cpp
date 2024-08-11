#include <iostream>
#include "MyDeque.hpp"
#include <string>

int main03() {
	MyDeque<int> Deque;

	int N;
	std::cin >> N;
	
	std::string line;

	while (N--) {
		std::cin >> line;
		if (line == "push_back") {
			int value;
			std::cin >> value;
			Deque.push_back(value);
		}
		else if (line == "push_front") {
			int value;
			std::cin >> value;
			Deque.push_front(value);
		}
		else if (line == "pop_back") {
			Deque.pop_back();
		}
		else if (line == "pop_front") {
			Deque.pop_front();
		}
		else if (line == "clear") {
			Deque.clear();
		}
		else if (line == "size") {
			std::cout << Deque.getSize() << std::endl;
		}
		else if (line == "get") {
			int index;
			std::cin >> index;
			std::cout << Deque[index] << std::endl;
		}
		else if (line == "print") {
			if (Deque.getSize()==0) {
				std::cout << "empty" << std::endl;
			}
			else {
				Deque.printElements();
			}
		}
	}

	return 0;
}