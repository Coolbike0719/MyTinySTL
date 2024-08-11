#include <iostream>
#include "MyMultiMap.hpp"

int main10() {
	MyMultiMap<int, int> MultiMap;

	int N;
	std::cin >> N;

	std::string line;

	while (N--) {
		std::cin >> line;
		if (line == "insert") {
			int key, value;
			std::cin >> key >> value;
			MultiMap.insert(key, value);
		}
		else if (line == "remove") {
			int key, value;
			std::cin >> key >> value;
			MultiMap.erase(key, value);
		}
		else if (line == "remove_all") {
			int key;
			std::cin >> key;
			MultiMap.erase(key);
		}
		else if (line == "at") {
			int key;
			std::cin >> key;
			try {
				std::list<int> values = MultiMap.at(key);
				for (const auto& value : values) {
					std::cout << value << " ";
				}
				std::cout << std::endl;
			}
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl;
			}
		}
		else if (line == "size") {
			std::cout << MultiMap.getSize() << std::endl;
		}
		else if (line == "clear") {
			MultiMap.clear();
		}
		else if (line == "print") {
			if (MultiMap.getSize() == 0) {
				std::cout << "MultiMap empty" << std::endl;
			}
			else {
				MultiMap.print();
			}
		}
		else if (line == "empty") {
			if (MultiMap.empty() == true) {
				std::cout << "true" << std::endl;
			}
			else {
				std::cout << "false" << std::endl;
			}
		}
	}

	return 0;
}