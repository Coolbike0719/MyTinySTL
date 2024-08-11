#pragma once

#include <iostream>
#include <stdexcept>

template <typename K, typename V>
class MyMap {
private:
    struct Node { // 基于二叉搜索树实现的map，比set多了[]和at()方法
        K key;
        V value;
        Node* left;
        Node* right;
        Node(const K& key, const V& value) : key(key), value(value), left(nullptr), right(nullptr) {}
    };

    Node* root; // map集合的根结点
    size_t size;

    // 私有的递归函数
    // 从node开始找位置插入一个值
    Node* insert(Node* node, const K& key, const V& value) {
        if (node == nullptr) { // 若当前为空，则创建新结点完成插入
            ++size;
            return new Node(key, value);
        }
        if (key < node->key) { // 若插入值小于当前结点则往左递归插入
            node->left = insert(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key, value);
        }
        return node; // 返回当前结点给上一级递归函数，如果是以上都不满足到的这说明就是当前结点
    }
    // 从node开始查找目标值
    Node* find(Node* node, const K& key) const {
        if (node == nullptr || node->key == key) {
            return node; // 空或者找到了就返回
        }
        if (key < node->key) {
            return find(node->left, key);
        }
        return find(node->right, key);
    }
    // 查找最小值，即最左结点，用于remove方法的删后维护
    Node* findMin(Node* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    // 从node开始找目标值删除
    Node* remove(Node* node, const K& key) {
        if (node == nullptr) { // 当前结点为空，没找到
            return node;
        }

        if (key < node->key) {
            node->left = remove(node->left, key);
        }
        else if (key > node->key) {
            node->right = remove(node->right, key);
        }
        else {  // 当前结点就是目标值，删除并维护二叉搜索树
            if (node->left == nullptr) {
                --size;
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {//如果左子树或右子树为空，那删除当前结点后返回另一个接上
                --size;
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // 当前结点同时有左右子树，找右子树的最小值结点顶替当前结点，然后递归删除右子树的该最小值
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key); // 这种情况不要--size，在右子树递归里会减的
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
            std::cout << node->key << ":" << node->value << " ";
            inOrder(node->right);
        }
    }

public:
    MyMap() : root(nullptr), size(0) {}

    ~MyMap() {
        clear(root);
    }
    // 封装成用户接口，递归和接口分开以简化代码
    // 用户插入、删除、查找等必然从集合的root开始
    void insert(const K& key, const V& value) {
        root = insert(root, key, value); // 当树为空时插入会更新root
    }
    void erase(const K& key) {
        root = remove(root, key); // 当删除的是根结点时会更新root
    }
    bool contains(const K& key) const {
        return find(root, key) != nullptr;
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
    V& operator[](const K& key) {
        Node* node = find(root, key);
        if (node == nullptr) { // []没找到就插入默认值返回
            insert(key, V());
            node = find(root, key);
        }
        return node->value;
    }
    V& at(const K& key) {
        Node* node = find(root, key);
        if (node == nullptr) {
            throw std::runtime_error("Key not found"); // 调用时记得捕获异常
        }
        return node->value;
    }
    const V& at(const K& key) const {
        Node* node = find(root, key);
        if (node == nullptr) {
            throw std::runtime_error("Key not found");
        }
        return node->value;
    }

    size_t getSize() const {
        return size;
    }
    bool empty() {
        return size == 0;
    }

};