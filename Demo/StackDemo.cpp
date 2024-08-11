#include <iostream>
#include "MyStack.hpp"
#include <stdexcept>

int main11() {
    // ʹ�� std::deque ��Ϊ�ײ�������ʾ��
    MyStack<int, std::deque<int>> stack;

    int N;
    std::cin >> N;

    std::string line;

    while (N--) {
        std::cin >> line;

        int element;
        if (line == "push") {
            std::cin >> element;
            stack.push(element);
        }
        if (line == "pop") {
            try {
                stack.pop();
            }
            catch (const std::runtime_error& e) {
                // �����κδ���
                continue;
            }
        }
        if (line == "top") {
            try {
                std::cout << stack.top() << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }
        }
        if (line == "size") {
            std::cout << stack.size() << std::endl;
        }
        if (line == "empty") {
            std::cout << (stack.empty() ? "true" : "false") << std::endl;
        }
    }
    return 0;
}