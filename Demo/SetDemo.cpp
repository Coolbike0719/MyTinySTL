#include <iostream>
#include "MySet.hpp"

int main05() {
	MySet<int> Set;

	int N;
	std::cin >> N;

	std::string line;

	while (N--) {
		std::cin >> line;
		if (line == "insert") {
			int value;
			std::cin >> value;
			Set.insert(value);
		}
		else if (line == "erase") {
			int value;
			std::cin >> value;
			Set.erase(value);
		}
		else if (line == "contains") {
			int value;
			std::cin >> value;
			if (Set.contains(value)) {
				std::cout << "true" << std::endl;
			}
			else {
				std::cout << "false" << std::endl;
			};
		}
		else if (line == "size") {
			std::cout << Set.getSize() << std::endl;
		}
		else if (line == "clear") {
			Set.clear();
		}
		else if (line == "print") {
			if (Set.getSize() == 0) {
				std::cout << "Set empty" << std::endl;
			}
			else {
				Set.print();
			}
		}
		else if (line == "empty") {
			if (Set.empty() == true) {
				std::cout << "true" << std::endl;
			}
			else {
				std::cout << "false" << std::endl;
			}
		}
	}

	return 0;
}