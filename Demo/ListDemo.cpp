#include <iostream>
#include "MyList.hpp"
#include <sstream> // getline istringstream
#include <string>

int main02() {
    // ����һ�� List ����
    MyList<int> List;

    int N;
    std::cin >> N;
    // ���߻س�
    getchar();
    std::string line;
    // ��������
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int value;

        if (command == "push_back") {
            iss >> value;
            List.push_back(value);
        }

        if (command == "push_front") {
            iss >> value;
            List.push_front(value);
        }

        if (command == "pop_back") {
            List.pop_back();
        }

        if (command == "pop_front") {
            List.pop_front();
        }

        if (command == "remove") {
            iss >> value;
            List.remove(value);
        }

        if (command == "clear") {
            List.clear();
        }

        if (command == "size") {
            std::cout << List.getSize() << std::endl;
        }

        if (command == "get") {
            iss >> value;
            std::cout << List[value] << std::endl;
            std::cout << "mytest" << std::endl;
        }

        if (command == "print") {
            if (List.getSize() == 0) {
                std::cout << "empty" << std::endl;
            }
            else {
                List.printElements();
            }
        }
    }
    List.printElements();
    std::cout << List << std::endl;
    return 0;
}