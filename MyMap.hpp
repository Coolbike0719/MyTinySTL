#pragma once

#include <iostream>
#include <stdexcept>

template <typename K, typename V>
class MyMap {
private:
    struct Node { // ���ڶ���������ʵ�ֵ�map����set����[]��at()����
        K key;
        V value;
        Node* left;
        Node* right;
        Node(const K& key, const V& value) : key(key), value(value), left(nullptr), right(nullptr) {}
    };

    Node* root; // map���ϵĸ����
    size_t size;

    // ˽�еĵݹ麯��
    // ��node��ʼ��λ�ò���һ��ֵ
    Node* insert(Node* node, const K& key, const V& value) {
        if (node == nullptr) { // ����ǰΪ�գ��򴴽��½����ɲ���
            ++size;
            return new Node(key, value);
        }
        if (key < node->key) { // ������ֵС�ڵ�ǰ���������ݹ����
            node->left = insert(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key, value);
        }
        return node; // ���ص�ǰ������һ���ݹ麯������������϶������㵽����˵�����ǵ�ǰ���
    }
    // ��node��ʼ����Ŀ��ֵ
    Node* find(Node* node, const K& key) const {
        if (node == nullptr || node->key == key) {
            return node; // �ջ����ҵ��˾ͷ���
        }
        if (key < node->key) {
            return find(node->left, key);
        }
        return find(node->right, key);
    }
    // ������Сֵ���������㣬����remove������ɾ��ά��
    Node* findMin(Node* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    // ��node��ʼ��Ŀ��ֵɾ��
    Node* remove(Node* node, const K& key) {
        if (node == nullptr) { // ��ǰ���Ϊ�գ�û�ҵ�
            return node;
        }

        if (key < node->key) {
            node->left = remove(node->left, key);
        }
        else if (key > node->key) {
            node->right = remove(node->right, key);
        }
        else {  // ��ǰ������Ŀ��ֵ��ɾ����ά������������
            if (node->left == nullptr) {
                --size;
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {//�����������������Ϊ�գ���ɾ����ǰ���󷵻���һ������
                --size;
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // ��ǰ���ͬʱ������������������������Сֵ��㶥�浱ǰ��㣬Ȼ��ݹ�ɾ���������ĸ���Сֵ
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key); // ���������Ҫ--size�����������ݹ�������
        }
        return node;
    }
    // �ݹ�ɾ����Ҫ�ݹ鴫�뵱ǰ��㣬ҲҪ��װ�ӿ�
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
    // ��������ݹ��ӡ���ʻᰴ�����ӡ
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
    // ��װ���û��ӿڣ��ݹ�ͽӿڷֿ��Լ򻯴���
    // �û����롢ɾ�������ҵȱ�Ȼ�Ӽ��ϵ�root��ʼ
    void insert(const K& key, const V& value) {
        root = insert(root, key, value); // ����Ϊ��ʱ��������root
    }
    void erase(const K& key) {
        root = remove(root, key); // ��ɾ�����Ǹ����ʱ�����root
    }
    bool contains(const K& key) const {
        return find(root, key) != nullptr;
    }
    void print() const {
        inOrder(root);
        std::cout << std::endl; // ���ݹ��ӡ����������лس�
    }
    void clear() {
        clear(root);
        root = nullptr;
        size = 0;
    }
    V& operator[](const K& key) {
        Node* node = find(root, key);
        if (node == nullptr) { // []û�ҵ��Ͳ���Ĭ��ֵ����
            insert(key, V());
            node = find(root, key);
        }
        return node->value;
    }
    V& at(const K& key) {
        Node* node = find(root, key);
        if (node == nullptr) {
            throw std::runtime_error("Key not found"); // ����ʱ�ǵò����쳣
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