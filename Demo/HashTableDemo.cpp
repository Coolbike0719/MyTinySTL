#include <iostream>
#include "MyHashTable.hpp"
#include <string>

int main04() {
	MyHashTable<int, int> HashTable;

	int N;
	std::cin >> N;

	std::string line;

	while (N--) {
		std::cin >> line;
		if (line == "insert") {
			int key, value;
			std::cin >> key >> value;
			HashTable.insert(key, value);
		}
		else if (line == "erase") {
			int key;
			std::cin >> key;
			HashTable.erase(key);
		}
		else if (line == "find") {
			int key;
			std::cin >> key;
			if (HashTable.find(key) == nullptr) {
				std::cout << "Not exist" << std::endl;
			};
		}
		else if (line == "size") {
			std::cout << HashTable.getSize() << std::endl;
		}
		else if (line == "clear") {
			HashTable.clear();
		}
		else if (line == "print") {
			if (HashTable.getSize() == 0) {
				std::cout << "empty" << std::endl;
			}
			else {
				HashTable.print();
			}
		}
	}

	return 0;
}