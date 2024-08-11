#pragma once

#include <iostream>

// ��set��ȣ�������Ӽ�������insert���Ӽ����жϣ�erase����count�޸ģ�����count��������Ԫ������
template <typename V>
class MyMultiSet { 
private:
    struct Node { // ���ڶ���������ʵ�ֵ�MultiSet
        V value;
        int count; // ��¼��Ԫ������
        Node* left;
        Node* right;
        Node(const V& value) : value(value), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root; // MultiSet���ϵĸ����
    size_t size;

    // ˽�еĵݹ麯��
    // ��node��ʼ��λ�ò���һ��ֵ
    Node* insert(Node* node, const V& value) {
        if (node == nullptr) { // ����ǰΪ�գ��򴴽��½����ɲ���
            ++size;
            return new Node(value);
        }

        if (value < node->value) { // ������ֵС�ڵ�ǰ���������ݹ����
            node->left = insert(node->left, value);
        }
        else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        else { // ˵��Ԫ���Ѵ���
            ++size;
            node->count++;
        }
        return node;
    }
    // ��node��ʼ����Ŀ��ֵ
    Node* find(Node* node, const V& value) const {
        if (node == nullptr || node->value == value) {
            return node; // �ջ����ҵ��˾ͷ���
        }
        if (value < node->value) {
            return find(node->left, value);
        }
        return find(node->right, value);
    }
    // ������Сֵ���������㣬����remove������ɾ��ά��
    Node* findMin(Node* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    // ��node��ʼ��Ŀ��ֵɾ��
    Node* remove(Node* node, const V& value) {
        if (node == nullptr) { // ��ǰ���Ϊ�գ�û�ҵ�
            return node;
        }
        if (value < node->value) {
            node->left = remove(node->left, value);
        }
        else if (value > node->value) {
            node->right = remove(node->right, value);
        }
        else {  // ��ǰ������Ŀ��ֵ��ɾ����ά��������������ɾ������Ŀ��ֵ
            size -= node->count;
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {//�����������������Ϊ�գ���ɾ����ǰ���󷵻���һ������
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // ��ǰ���ͬʱ������������������������Сֵ��㶥�浱ǰ��㣬Ȼ��ݹ�ɾ���������ĸ���Сֵ
            Node* temp = findMin(node->right);
            node->value = temp->value;
            node->count = temp->count;
            temp->count = 0; // �˴��ѽ�tempת�Ƶ�node������ԭtemp��count��Ϊ0����ֹ�ݹ�ʱsize�ټ�temp->count
            node->right = remove(node->right, temp->value);
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
            std::cout << node->value << " ";
            inOrder(node->right);
        }
    }

public:
    MyMultiSet() : root(nullptr), size(0) {}

    ~MyMultiSet() {
        clear(root);
    }
    // ��װ���û��ӿڣ��ݹ�ͽӿڷֿ��Լ򻯴���
    // �û����롢ɾ�������ҵȱ�Ȼ�Ӽ��ϵ�root��ʼ
    void insert(const V& value) {
        root = insert(root, value); // ����Ϊ��ʱ��������root
    }

    void erase(const V& value) {
        root = remove(root, value); // ��ɾ�����Ǹ����ʱ�����root
    }

    bool contains(const V& value) const {
        return find(root, value) != nullptr;
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

    size_t getSize() const{
        return size;
    }

    bool empty() {
        return size == 0;
    }

    // Multi����count��������Ŀ��ֵ�ļ���
    int count(const V& value) const {
        Node* node = find(root, value);
        return node ? node->count : 0;
    }
};