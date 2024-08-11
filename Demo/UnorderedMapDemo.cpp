#include <iostream>
#include "MyUnorderedMap.hpp"

int main09() {
	MyUnorderedMap<int, int> UnorderedMap;

	int N;
	std::cin >> N;

	std::string line;

	while (N--) {
		std::cin >> line;
		if (line == "insert") {
			int key, value;
			std::cin >> key >> value;
			UnorderedMap.insert(key, value);
		}
		else if (line == "erase") {
			int key;
			std::cin >> key;
			UnorderedMap.erase(key);
		}
		else if (line == "find") {
			int key;
			std::cin >> key;
			if (UnorderedMap.find(key)) {
				std::cout << "true" << std::endl;
			}
			else {
				std::cout << "false" << std::endl;
			};
		}
		else if (line == "size") {
			std::cout << UnorderedMap.size() << std::endl;
		}
		else if (line == "clear") {
			UnorderedMap.clear();
		}
		else if (line == "empty") {
			if (UnorderedMap.empty() == true) {
				std::cout << "true" << std::endl;
			}
			else {
				std::cout << "false" << std::endl;
			}
		}
	}

	return 0;
}