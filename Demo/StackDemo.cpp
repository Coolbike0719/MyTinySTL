#include <iostream>
#include "MyStack.hpp"
#include <stdexcept>

int main11() {
    // 使用 std::deque 作为底层容器的示例
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
                // 不做任何处理
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