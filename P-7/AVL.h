//AVL.h

#pragma once

#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

template <typename T>
class AVL {
private:
    struct Node {
        T key;
        Node *left;
        Node *right;
        int height; // Height of the subtree rooted at this node
        int size;   // Number of nodes in the subtree rooted here
        long long sum; // Sum of keys in the subtree rooted here

        Node(T k) : key(k), left(nullptr), right(nullptr), height(0), size(1), sum(k) {}
    };

    Node *root;

    // --- Core Utility Helpers ---

    int getHeight(Node *n) {
        return (n == nullptr) ? -1 : n->height;
    }

    int getSize(Node *n) {
        return (n == nullptr) ? 0 : n->size;
    }

    long long getSum(Node *n) {
        return (n == nullptr) ? 0 : n->sum;
    }

    int getBalanceFactor(Node *n) {
        if (n == nullptr) return 0;
        return getHeight(n->left) - getHeight(n->right);
    }

    void updateNode(Node *n) {
        if (n == nullptr) return;
        n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
        n->size = 1 + getSize(n->left) + getSize(n->right);
        n->sum = n->key + getSum(n->left) + getSum(n->right);
    }

    // --- Rotation Functions ---
    Node* rightRotate(Node* y){
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateNode(y);
        updateNode(x);
        return x;
    }
    Node* leftRotate(Node* x){
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateNode(x);
        updateNode(y);
        return y;
    }

    // --- Private helpers ---

    Node* insert_helper(Node* node, T key) {
        // 1. Standard BST Insert
        if (node == nullptr) {
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insert_helper(node->left, key);
        } else if (key > node->key) {
            node->right = insert_helper(node->right, key);
        } else {        // avoids insertion of duplicate keys
            return node;
        }

        // 2. Update this ancestor node's data
        updateNode(node);

        // 3. Get the balance factor
        int balance = getBalanceFactor(node);

        // 4. Rebalance if needed (run only if unbalanced - node->left or node->right does not get reached if tree is not left heavy or right heavy)

        // Left-Left Case
        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }

        // Right-Right Case
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }

        // Left-Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right-Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // 5. Return the (possibly new) root of this subtree
        return node;
    }

    //helper to find inorder successor
    Node* findMin(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    Node* delete_helper(Node* node, T key) {
        // 1. Standard BST Delete
        if (node == nullptr) {
            return node; // Key not found
        }

        if (key < node->key) {
            node->left = delete_helper(node->left, key);
        } else if (key > node->key) {
            node->right = delete_helper(node->right, key);
        } else {
            // handling the case when not both children present - leaf node or 1 child
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = (node->left != nullptr) ? node->left : node->right;    // gets the possibly non-null child to replace current node with
                if (temp == nullptr) {      // case of a leaf node
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {        // case when both children are present
                Node* temp = findMin(node->right);
                node->key = temp->key;
                node->right = delete_helper(node->right, temp->key);
            }
        }

        if (node == nullptr) {
            return node;
        }

        updateNode(node);

        int balance = getBalanceFactor(node);


        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }

        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }

        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left); // Straighten the "kink"
            return rightRotate(node);
        }

        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* next_helper(T key){
        Node* successor = nullptr;
        Node* cur = root;
        while(cur != nullptr){
            if(cur->key > key){
                successor = cur;
                cur = cur->left;
            }
            else if(cur->key <= key) cur = cur->right;
        }
        return successor;
    }

    Node* prev_helper(T key){
        Node* predecessor = nullptr;
        Node* cur = root;
        while(cur != nullptr){
            if(cur->key < key){
                predecessor = cur;
                cur = cur->right;
            }
            else if(cur->key >= key) cur = cur->left;
        }
        return predecessor;
    }

    void printInorder_helper(Node* node) {
        if (node == nullptr) return;
        printInorder_helper(node->left);
        cout<<node->key<<' ';
        printInorder_helper(node->right);
    }

    void printPreorder_helper(Node* node) {
        if (node == nullptr) return;
        cout<<node->key<<' ';
        printPreorder_helper(node->left);
        printPreorder_helper(node->right);
    }

    void printPostorder_helper(Node* node) {
        if (node == nullptr) return;
        printPostorder_helper(node->left);
        printPostorder_helper(node->right);
        cout<<node->key<<' ';
    }

    void printLevelOrder_helper(Node* node) {
        if (node == nullptr) return;

        std::queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* x = q.front();
            q.pop();

            std::cout << x->key << ' ';

            if (x->left != nullptr) q.push(x->left);
            if (x->right != nullptr) q.push(x->right);
        }
    }

    int countLessThan_helper(Node* node, T x){
        if(node == nullptr) return 0;
        if(node->key < x){
            return 1 + getSize(node->left) + countLessThan_helper(node->right,x);
        } else{
            return countLessThan_helper(node->left,x);
        }
    }

    int countLessThanOrEqual_helper(Node* node, T x){
        if(node == nullptr) return 0;
        if(node->key <= x){
            return 1 + getSize(node->left) + countLessThanOrEqual_helper(node->right,x);
        } else{
            return countLessThanOrEqual_helper(node->left,x);
        }
    }

    long long sumLessThan_helper(Node* node, T x){
        if(node == nullptr) return 0;
        if(node->key < x){
            return node->key + getSum(node->left) + sumLessThan_helper(node->right,x);
        } else{
            return sumLessThan_helper(node->left,x);
        }
    }

    long long sumLessThanOrEqual_helper(Node* node, T x){
        if(node == nullptr) return 0;
        if(node->key <= x){
            return node->key + getSum(node->left) + sumLessThanOrEqual_helper(node->right,x);
        } else{
            return sumLessThanOrEqual_helper(node->left,x);
        }
    }

    Node* select_helper(Node* node, int k) {
        if (node == nullptr) {
            return nullptr;
        }

        int left_size = getSize(node->left);

        if (k == left_size + 1) {
            // Case 1: The root is the k-th element
            return node;
        }
        else if (k <= left_size) {
            // Case 2: k-th element is in the left subtree
            return select_helper(node->left, k);
        }
        else {
            // Case 3: k-th element is in the right subtree
            // We've skipped left_size + 1 nodes, so we look for the
            // (k - left_size - 1)-th element on the right.
            return select_helper(node->right, k - left_size - 1);
        }
    }

    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);

            delete node;
        }
    }

public:
    AVL() : root(nullptr) {}

    ~AVL() {
        clear(root);
    }

    void insert(T key) {
        root = insert_helper(root, key);
    }

    void delete_node(T key) {
        root = delete_helper(root, key);
    }

    bool find(T key){
        Node* cur = root;
        while(cur != nullptr){
            if(cur->key == key) return true;
            if(cur->key > key) cur = cur->left;
            else if(cur->key < key) cur = cur->right;
        }
        return false;
    }

    void prev(T key){
        Node* p = prev_helper(key);
        if (p == nullptr) {
            std::cout << "NONE\n";
        } else {
            std::cout << p->key << "\n";
        }
    }

    void next(T key) {
        Node* n = next_helper(key);
        if (n == nullptr) {
            std::cout << "NONE\n";
        } else {
            std::cout << n->key << "\n";
        }
    }

    int range_count(T L, T R) {
        return countLessThanOrEqual_helper(root, R) - countLessThan_helper(root,L);
    }

    void select(int k) {
        if (k < 1 || k > getSize(root)) {
            std::cout << "INVALID\n";
            return;
        }

        Node* result = select_helper(root, k);
        if (result != nullptr) {
            std::cout << result->key << "\n";
        } else {
            std::cout << "INVALID\n";
        }
    }

    void rank(T key){
        int result = countLessThan_helper(root, key);
        cout<<result<<'\n';
    }

    void range_sum(T L, T R) {
        long long sum_le_R = sumLessThanOrEqual_helper(root, R);
        long long sum_lt_L = sumLessThan_helper(root, L);
        std::cout << (sum_le_R - sum_lt_L) << "\n";
    }

    void print(const std::string& type) {
        if (root == nullptr) {
            std::cout << "EMPTY\n";
            return;
        }

        if (type == "IN") printInorder_helper(root);
        else if (type == "PRE") printPreorder_helper(root);
        else if (type == "POST") printPostorder_helper(root);
        else if (type == "LEVEL") printLevelOrder_helper(root);

        std::cout << "\n";
    }

};