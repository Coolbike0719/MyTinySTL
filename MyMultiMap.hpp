#pragma once
#include <list>
#include <iostream>

// ��Multiset��ȣ�map����������Ԫ��ͬ����ֵͬ���ʲ�����count��Ҫ������洢
template <typename K, typename V>
class MyMultiMap {
private:
    struct Node { // ���ڶ���������ʵ�ֵ�MultiMap
        K key;
        std::list<V> values; // ʹ������洢��ֵͬ��ע��ͬ��ֵͬҲ�����������������һ���ṹ��
        Node* left;
        Node* right;
        Node(const K& key, const V& value) : key(key), values(1,value), left(nullptr), right(nullptr) {}
    };

    Node* root; // MultiMap���ϵĸ����
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
        else { // ˵��keyֵ�Ѵ���
            ++size;
            node->values.push_back(value); // �������ͬ��ֵͬ�����Ҳ������ȥ
        }
        return node;
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
    // ɾ��ָ��key������Ԫ��
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
        else {  // ��ǰ������Ŀ��ֵ��ɾ����ά��������������ɾ������Ŀ��ֵ
            size -= node->values.size();
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
            node->key = temp->key;
            node->values = std::move(temp->values); // Ҫ��temp�������ƹ�ȥ
            node->right = remove(node->right, temp->key);
        }
        return node;
    }
    // ɾ��ָ��key��ָ��value
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
        else { // key�ҵ��ˣ���ʼ��value
            auto it = std::find(node->values.begin(), node->values.end(), value);
            if (it != node->values.end()) {
                node->values.erase(it);
                --size;
            }
            // ������ڸý�������Ϊ�գ�ɾ����㲢���ж�����������ά��
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
                node->right = remove(node->right, temp->key); // ��temp��������ȥ�ˣ���ȻҲ������ɾ��ԭtemp
            }
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
            std::cout << node->key << " ";
            for (const auto& value : node->values) { // ���������ӡ����ֵ
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
    // ��װ���û��ӿڣ��ݹ�ͽӿڷֿ��Լ򻯴���
    // �û����롢ɾ�������ҵȱ�Ȼ�Ӽ��ϵ�root��ʼ
    void insert(const K& key, const V& value) {
        root = insert(root, key, value); // ����Ϊ��ʱ��������root
    }

    void erase(const K& key) {
        root = remove(root, key); // ��ɾ�����Ǹ����ʱ�����root
    }
    void erase(const K& key, const V& value) {
        root = remove(root, key, value); // ��ɾ�����Ǹ����ʱ�����root
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

    size_t getSize() const {
        return size;
    }

    bool empty() {
        return size == 0;
    }

    // ����[]�������
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
            throw std::runtime_error("Key not found"); // ����ʱ�ǵò����쳣
        }
        return node->values;
    }
};