#pragma once
#include <list>
#include <iostream>

// 和Multiset相比，map可以允许多个元素同键不同值，故不能用count，要用链表存储
template <typename K, typename V>
class MyMultiMap {
private:
    struct Node { // 基于二叉搜索树实现的MultiMap
        K key;
        std::list<V> values; // 使用链表存储不同值，注意同键同值也互相独立，或者再套一个结构体
        Node* left;
        Node* right;
        Node(const K& key, const V& value) : key(key), values(1,value), left(nullptr), right(nullptr) {}
    };

    Node* root; // MultiMap集合的根结点
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
        else { // 说明key值已存在
            ++size;
            node->values.push_back(value); // 如果出现同键同值的情况也会塞进去
        }
        return node;
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
    // 删除指定key的所有元素
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
        else {  // 当前结点就是目标值，删除并维护二叉搜索树，删除所有目标值
            size -= node->values.size();
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
            node->key = temp->key;
            node->values = std::move(temp->values); // 要把temp的链表移过去
            node->right = remove(node->right, temp->key);
        }
        return node;
    }
    // 删除指定key的指定value
    Node* remove(Node* node, const K& key, const V& value) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->left = remove(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = remove(node->right, key, value);
        }
        else { // key找到了，开始找value
            auto it = std::find(node->values.begin(), node->values.end(), value);
            if (it != node->values.end()) {
                node->values.erase(it);
                --size;
            }
            // 如果现在该结点的链表为空，删除结点并进行二叉搜索树的维护
            if (node->values.empty()) {
                if (node->left == nullptr) {
                    Node* temp = node->right;
                    delete node;
                    return temp;
                }
                else if (node->right == nullptr) {
                    Node* temp = node->left;
                    delete node;
                    return temp;
                }
                Node* temp = findMin(node->right);
                node->key = temp->key;
                node->values = std::move(temp->values);
                node->right = remove(node->right, temp->key); // 把temp整个换过去了，自然也是整个删除原temp
            }
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
            std::cout << node->key << " ";
            for (const auto& value : node->values) { // 遍历链表打印所有值
                std::cout << value << " ";
            }
            std::cout << std::endl;
            inOrder(node->right);
        }
    }

public:
    MyMultiMap() : root(nullptr), size(0) {}

    ~MyMultiMap() {
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
    void erase(const K& key, const V& value) {
        root = remove(root, key, value); // 当删除的是根结点时会更新root
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

    size_t getSize() const {
        return size;
    }

    bool empty() {
        return size == 0;
    }

    // 重载[]随机访问
    V& operator[](const K& key) {
        V* node = find(root, key);
        if (node == nullptr) {
            insert(key, V());
            node = find(root, key);
        }
        return *node;
    }
    std::list<V>& at(const K& key) {
        Node* node = find(root, key);
        if (node == nullptr) {
            throw std::runtime_error("Key not found"); // 调用时记得捕获异常
        }
        return node->values;
    }
};