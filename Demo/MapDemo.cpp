#include <iostream>
#include "MyMap.hpp"

int main08() {
	MyMap<int, int> Map;

	int N;
	std::cin >> N;

	std::string line;

	while (N--) {
		std::cin >> line;
		if (line == "insert") {
			int key;
			int value;
			std::cin >> key >> value;
			Map.insert(key, value);
		}
		else if (line == "erase") {
			int key;
			std::cin >> key;
			Map.erase(key);
		}
		else if (line == "contains") {
			int key;
			std::cin >> key;
			if (Map.contains(key)) {
				std::cout << "true" << std::endl;
			}
			else {
				std::cout << "false" << std::endl;
			};
		}
		else if (line == "at") {
			int key;
			std::cin >> key;
			try {
				std::cout << Map.at(key) << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cout << e.what() << std::endl;
			}
		}
		else if (line == "size") {
			std::cout << Map.getSize() << std::endl;
		}
		else if (line == "clear") {
			Map.clear();
		}
		else if (line == "print") {
			if (Map.getSize() == 0) {
				std::cout << "Map empty" << std::endl;
			}
			else {
				Map.print();
			}
		}
		else if (line == "empty") {
			if (Map.empty() == true) {
				std::cout << "true" << std::endl;
			}
			else {
				std::cout << "false" << std::endl;
			}
		}
	}

	return 0;
}