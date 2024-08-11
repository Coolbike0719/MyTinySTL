#include <iostream>
#include "MyMultiSet.hpp"

int main07() {
	MyMultiSet<int> MultiSet;

	int N;
	std::cin >> N;

	std::string line;

	while (N--) {
		std::cin >> line;
		if (line == "insert") {
			int value;
			std::cin >> value;
			MultiSet.insert(value);
		}
		else if (line == "erase") {
			int value;
			std::cin >> value;
			MultiSet.erase(value);
		}
		else if (line == "contains") {
			int value;
			std::cin >> value;
			if (MultiSet.contains(value)) {
				std::cout << "true" << std::endl;
			}
			else {
				std::cout << "false" << std::endl;
			};
		}
		else if (line == "count") {
			int value;
			std::cin >> value;
			std::cout << MultiSet.count(value) << std::endl;
		}
		else if (line == "size") {
			std::cout << MultiSet.getSize() << std::endl;
		}
		else if (line == "clear") {
			MultiSet.clear();
		}
		else if (line == "print") {
			if (MultiSet.getSize() == 0) {
				std::cout << "MultiSet empty" << std::endl;
			}
			else {
				MultiSet.print();
			}
		}
		else if (line == "empty") {
			if (MultiSet.empty() == true) {
				std::cout << "true" << std::endl;
			}
			else {
				std::cout << "false" << std::endl;
			}
		}
	}

	return 0;
}