#pragma once

#include <iostream>

// 和set相比：结点增加计数器，insert增加计数判断，erase增加count修改，增加count方法返回元素数量
template <typename V>
class MyMultiSet { 
private:
    struct Node { // 基于二叉搜索树实现的MultiSet
        V value;
        int count; // 记录该元素数量
        Node* left;
        Node* right;
        Node(const V& value) : value(value), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root; // MultiSet集合的根结点
    size_t size;

    // 私有的递归函数
    // 从node开始找位置插入一个值
    Node* insert(Node* node, const V& value) {
        if (node == nullptr) { // 若当前为空，则创建新结点完成插入
            ++size;
            return new Node(value);
        }

        if (value < node->value) { // 若插入值小于当前结点则往左递归插入
            node->left = insert(node->left, value);
        }
        else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        else { // 说明元素已存在
            ++size;
            node->count++;
        }
        return node;
    }
    // 从node开始查找目标值
    Node* find(Node* node, const V& value) const {
        if (node == nullptr || node->value == value) {
            return node; // 空或者找到了就返回
        }
        if (value < node->value) {
            return find(node->left, value);
        }
        return find(node->right, value);
    }
    // 查找最小值，即最左结点，用于remove方法的删后维护
    Node* findMin(Node* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    // 从node开始找目标值删除
    Node* remove(Node* node, const V& value) {
        if (node == nullptr) { // 当前结点为空，没找到
            return node;
        }
        if (value < node->value) {
            node->left = remove(node->left, value);
        }
        else if (value > node->value) {
            node->right = remove(node->right, value);
        }
        else {  // 当前结点就是目标值，删除并维护二叉搜索树，删除所有目标值
            size -= node->count;
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {//如果左子树或右子树为空，那删除当前结点后返回另一个接上
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // 当前结点同时有左右子树，找右子树的最小值结点顶替当前结点，然后递归删除右子树的该最小值
            Node* temp = findMin(node->right);
            node->value = temp->value;
            node->count = temp->count;
            temp->count = 0; // 此处已将temp转移到node处，将原temp的count置为0，防止递归时size再减temp->count
            node->right = remove(node->right, temp->value);
        }
        return node;
    }
    // 递归删除，要递归传入当前结点，也要封装接口
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
    // 中序遍历递归打印，故会按升序打印
    void inOrder(Node* node) const {
        if (node != nullptr) {
            inOrder(node->left);
            std::cout << node->value << " ";
            inOrder(node->right);
        }
    }

public:
    MyMultiSet() : root(nullptr), size(0) {}

    ~MyMultiSet() {
        clear(root);
    }
    // 封装成用户接口，递归和接口分开以简化代码
    // 用户插入、删除、查找等必然从集合的root开始
    void insert(const V& value) {
        root = insert(root, value); // 当树为空时插入会更新root
    }

    void erase(const V& value) {
        root = remove(root, value); // 当删除的是根结点时会更新root
    }

    bool contains(const V& value) const {
        return find(root, value) != nullptr;
    }

    void print() const {
        inOrder(root);
        std::cout << std::endl; // 不递归打印不了这个换行回车
    }

    void clear() {
        clear(root);
        root = nullptr;
        size = 0;
    }

    size_t getSize() const{
        return size;
    }

    bool empty() {
        return size == 0;
    }

    // Multi增加count方法返回目标值的计数
    int count(const V& value) const {
        Node* node = find(root, value);
        return node ? node->count : 0;
    }
};