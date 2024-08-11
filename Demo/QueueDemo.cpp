#include <iostream>
#include "MyQueue.hpp"
#include <stdexcept>

int main12() {
    // 使用 std::deque 作为底层容器的示例
    MyQueue<int, std::deque<int>> stack;

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
        else if (line == "pop") {
            try {
                stack.pop();
            }
            catch (const std::runtime_error& e) {
                // 不做任何处理
                continue;
            }
        }
        else if (line == "front") {
            try {
                std::cout << stack.front() << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }
        }
        else if (line == "back") {
            try {
                std::cout << stack.back() << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }
        }
        else if (line == "size") {
            std::cout << stack.size() << std::endl;
        }
        else if (line == "empty") {
            std::cout << (stack.empty() ? "true" : "false") << std::endl;
        }
    }
    return 0;
}