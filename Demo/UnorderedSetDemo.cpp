#include <iostream>
#include "MyUnorderedSet.hpp"

int main06() {
	MyUnorderedSet<int> UnorderedSet;

	int N;
	std::cin >> N;

	std::string line;

	while (N--) {
		std::cin >> line;
		if (line == "insert") {
			int key;
			std::cin >> key;
			UnorderedSet.insert(key);
		}
		else if (line == "erase") {
			int key;
			std::cin >> key;
			UnorderedSet.erase(key);
		}
		else if (line == "find") {
			int key;
			std::cin >> key;
			if (UnorderedSet.find(key)) {
				std::cout << "true" << std::endl;
			}
			else {
				std::cout << "false" << std::endl;
			};
		}
		else if (line == "size") {
			std::cout << UnorderedSet.size() << std::endl;
		}
		else if (line == "clear") {
			UnorderedSet.clear();
		}
		else if (line == "empty") {
			if (UnorderedSet.empty() == true) {
				std::cout << "true" << std::endl;
			}
			else {
				std::cout << "false" << std::endl;
			}
		}
	}

	return 0;
}