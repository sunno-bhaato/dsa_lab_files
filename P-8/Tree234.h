#pragma once

#include <iostream>
#include <queue>
#include <string>    // Added for main()
#include <sstream>   // Added for main()
#include <vector>    // Added for main() (BULK)

using namespace std;

/**
 * @brief Struct for Q4 (Key-Value Pairs)
 *
 * This struct will be the type 'T' for the Q4 tree.
 * The 2-3-4 tree's comparison logic will work automatically
 * because we've overloaded the comparison operators.
 */
struct KeyValue {
    int key;
    int val;

    // --- Comparison operators (based only on key) ---
    bool operator<(const KeyValue& other) const { return key < other.key; }
    bool operator>(const KeyValue& other) const { return key > other.key; }
    bool operator==(const KeyValue& other) const { return key == other.key; }

    // --- Operators to allow comparing with a plain int key ---
    // These are helpful for searching (e.g., KeyValue{key, 0})
    bool operator<(int k) const { return key < k; }
    bool operator>(int k) const { return key > k; }
    bool operator==(int k) const { return key == k; }
    friend bool operator<(int k, const KeyValue& kv) { return k < kv.key; }
    friend bool operator>(int k, const KeyValue& kv) { return k > kv.key; }
    friend bool operator==(int k, const KeyValue& kv) { return k == kv.key; }


    /**
     * @brief Overload the << operator to print "key:val"
     * This fulfills the output requirement for Q4's RANGE command. [cite: 146]
     */
    friend ostream& operator<<(ostream& os, const KeyValue& kv) {
        os << kv.key << ":" << kv.val;
        return os;
    }
};


template <typename T>
class Tree234{
private:
    struct Node{
        int num_keys;
        bool is_leaf;

        T keys[3];
        Node* children[4];

        Node(bool leaf_status) : num_keys(0), is_leaf(leaf_status) {
            for(int i = 0; i<4; i++) children[i] = nullptr;
        }
    };

    Node* root;

    void split_child(Node* parent, int child_index) {

        Node* child_to_split = parent->children[child_index];
        T middle_key = child_to_split->keys[1];

        Node* right_sibling = new Node(child_to_split->is_leaf);
        right_sibling->num_keys = 1;
        right_sibling->keys[0] = child_to_split->keys[2];

        if (!child_to_split->is_leaf) {
            right_sibling->children[0] = child_to_split->children[2];
            right_sibling->children[1] = child_to_split->children[3];
        }

        child_to_split->num_keys = 1;

        for (int j = parent->num_keys; j > child_index; j--) {
            parent->children[j + 1] = parent->children[j];
        }

        parent->children[child_index + 1] = right_sibling;

        for (int j = parent->num_keys - 1; j >= child_index; j--) {
            parent->keys[j + 1] = parent->keys[j];
        }

        parent->keys[child_index] = middle_key;
        parent->num_keys++;
    }

    void insert_into_non_full(Node* x, T key){

        if(x->is_leaf){
            bool done = false;
            int i = 0;
            // Find position to insert
            while (i < x->num_keys && key > x->keys[i]) {
                i++;
            }
            // Shift keys to the right
            for(int j = x->num_keys; j > i; j--) {
                x->keys[j] = x->keys[j-1];
            }
            // Insert new key
            x->keys[i] = key;
            x->num_keys++;
            return;
        }

        else {

            int i = 0;
            while (i < x->num_keys && key > x->keys[i]) {
                i++;
            }

            if (x->children[i]->num_keys == 3) {
                split_child(x, i);
                if (key > x->keys[i]) {
                    i++; // If so, we go to the new child at i+1, otherwise it stays at i - left of where x[middle_key] got inserted.
                }
            }

            insert_into_non_full(x->children[i], key);
        }
    }


    void printInorder_helper(Node* node) {
        if (node == nullptr) {
            return;
        }

        int i;
        for (i = 0; i < node->num_keys; i++) {
            // 1. Recurse on the child subtree
            if (!node->is_leaf) {
                printInorder_helper(node->children[i]);
            }
            // 2. Print the key
            std::cout << node->keys[i] << " ";
        }

        // 3. Recurse on the last child (children[i])
        if (!node->is_leaf) {
            printInorder_helper(node->children[i]);
        }
    }

    //DELETE helpers
    void delete_helper(Node* node, T key) {

        // 1. Find the first key >= the key we want to delete
        int i = 0;
        while (i < node->num_keys && key > node->keys[i]) {
            i++;
        }

        // --- CASE 1: The key is in THIS node ---
        if (i < node->num_keys && key == node->keys[i]) {
            if (node->is_leaf) {
                delete_from_leaf(node, i);
            } else {
                delete_from_internal(node, i);
            }
        }
            // --- CASE 2: The key is in a child subtree ---
        else {
            if (node->is_leaf) {
                // We're at a leaf and didn't find the key.
                return;
            }

            // 'i' is the index of the child to descend into.
            // Check if this child is a 2-node (has 1 key).
            if (node->children[i]->num_keys == 1) {
                // Fix a 2-node before proceeding
                fill_child(node, i);
            }

            // After 'fill_child', the child at 'i' might have been
            // merged with the one at 'i-1'.
            // We re-check the index 'i' relative to the parent's keys.
            int i_new = 0;
            while (i_new < node->num_keys && key > node->keys[i_new]) {
                i_new++;
            }

            delete_helper(node->children[i_new], key);

        }
    }

    /**
     * Helper to fix a 2-node child before descending into it.
     */
    void fill_child(Node* parent, int child_index) {
        // Try borrowing from the left sibling
        if (child_index != 0 && parent->children[child_index - 1]->num_keys > 1) {
            borrow_from_prev(parent, child_index);
        }
            // Try borrowing from the right sibling
        else if (child_index != parent->num_keys && parent->children[child_index + 1]->num_keys > 1) {
            borrow_from_next(parent, child_index);
        }
            // Must merge siblings
        else {
            if (child_index != parent->num_keys) {
                // Merge with right sibling
                merge_children(parent, child_index);
            } else {
                // At the end, merge with left sibling
                merge_children(parent, child_index - 1);
            }
        }
    }

    /**
     * CASE 1a: Key is in a leaf node. Just remove it.
     */
    void delete_from_leaf(Node* node, int key_index) {
        // Shift all keys to the right of key_index one position left
        for (int i = key_index; i < node->num_keys - 1; i++) {
            node->keys[i] = node->keys[i + 1];
        }
        node->num_keys--;
    }

    /**
     * CASE 1b: Key is in an internal node.
     */
    void delete_from_internal(Node* node, int key_index) {
        T key = node->keys[key_index];

        // If left child has > 1 key, replace with predecessor
        if (node->children[key_index]->num_keys > 1) {
            T predecessor = find_predecessor(node->children[key_index]);
            node->keys[key_index] = predecessor;
            delete_helper(node->children[key_index], predecessor);
        }
            // If right child has > 1 key, replace with successor
        else if (node->children[key_index + 1]->num_keys > 1) {
            T successor = find_successor(node->children[key_index + 1]);
            node->keys[key_index] = successor;
            delete_helper(node->children[key_index + 1], successor);
        }
            // If both children are 2-nodes, merge them
        else {
            merge_children(node, key_index);
            delete_helper(node->children[key_index], key);
        }
    }

    /**
     * Helper to find the largest key in the subtree (predecessor).
     */
    T find_predecessor(Node* node) {
        while (!node->is_leaf) {
            node = node->children[node->num_keys];
        }
        return node->keys[node->num_keys - 1];
    }

    /**
     * Helper to find the smallest key in the subtree (successor).
     */
    T find_successor(Node* node) {
        while (!node->is_leaf) {
            node = node->children[0];
        }
        return node->keys[0];
    }

    /**
     * Rotates a key from left_sibling -> parent -> node
     */
    void borrow_from_prev(Node* parent, int child_index) {
        Node* child = parent->children[child_index];
        Node* left_sibling = parent->children[child_index - 1];

        // Shift all keys/children in 'child' one to the right
        for (int i = child->num_keys - 1; i >= 0; i--) {
            child->keys[i + 1] = child->keys[i];
        }
        if (!child->is_leaf) {
            for (int i = child->num_keys; i >= 0; i--) {
                child->children[i + 1] = child->children[i];
            }
        }

        // Move parent key down to 'child'
        child->keys[0] = parent->keys[child_index - 1];
        // Move sibling's last child to 'child's first child
        if (!child->is_leaf) {
            child->children[0] = left_sibling->children[left_sibling->num_keys];
        }

        // Move sibling's last key up to 'parent'
        parent->keys[child_index - 1] = left_sibling->keys[left_sibling->num_keys - 1];

        child->num_keys++;
        left_sibling->num_keys--;
    }

    /**
     * Rotates a key from node <- parent <- right_sibling
     */
    void borrow_from_next(Node* parent, int child_index) {
        Node* child = parent->children[child_index];
        Node* right_sibling = parent->children[child_index + 1];

        // Move parent key down to end of 'child'
        child->keys[child->num_keys] = parent->keys[child_index];
        // Move sibling's first child to 'child's last child
        if (!child->is_leaf) {
            child->children[child->num_keys + 1] = right_sibling->children[0];
        }

        // Move sibling's first key up to 'parent'
        parent->keys[child_index] = right_sibling->keys[0];

        // Shift all keys/children in 'right_sibling' one to the left
        for (int i = 1; i < right_sibling->num_keys; i++) {
            right_sibling->keys[i - 1] = right_sibling->keys[i];
        }
        if (!right_sibling->is_leaf) {
            for (int i = 1; i <= right_sibling->num_keys; i++) {
                right_sibling->children[i - 1] = right_sibling->children[i];
            }
        }

        child->num_keys++;
        right_sibling->num_keys--;
    }

    /**
     * Merges child[child_index] and child[child_index + 1]
     */
    void merge_children(Node* parent, int child_index) {
        Node* left_child = parent->children[child_index];
        Node* right_child = parent->children[child_index + 1];

        // 1. Move parent key down into left_child
        left_child->keys[left_child->num_keys] = parent->keys[child_index];

        // 2. Move all keys from right_child into left_child
        for (int i = 0; i < right_child->num_keys; i++) {
            left_child->keys[left_child->num_keys + 1 + i] = right_child->keys[i];
        }

        // 3. Move all children from right_child into left_child
        if (!left_child->is_leaf) {
            for (int i = 0; i <= right_child->num_keys; i++) {
                left_child->children[left_child->num_keys + 1 + i] = right_child->children[i];
            }
        }

        // 4. Update key/child counts
        left_child->num_keys += right_child->num_keys + 1;

        // 5. Shift keys and children in parent left
        for (int i = child_index; i < parent->num_keys - 1; i++) {
            parent->keys[i] = parent->keys[i + 1];
        }
        for (int i = child_index + 1; i < parent->num_keys; i++) {
            parent->children[i] = parent->children[i + 1];
        }

        parent->num_keys--;

        // 6. Delete the now-empty right child
        delete right_child;
    }


    void printLevelOrder_helper(Node* node) {
        if (node == nullptr) return;

        std::queue<Node*> q;
        q.push(node);

        while (!q.empty()) {

            int level_size = q.size();

            for (int i = 0; i < level_size; i++) {

                // 1. Dequeue a node
                Node* current = q.front();
                q.pop();

                // 2. Print its keys in the format [k1 k2 ...]
                std::cout << "[";
                for (int k = 0; k < current->num_keys; k++) {
                    std::cout << current->keys[k];
                    if (k < current->num_keys - 1) {
                        std::cout << " ";
                    }
                }
                std::cout << "] ";

                // 3. Enqueue all its children for the next level
                if (!current->is_leaf) {
                    for (int c = 0; c <= current->num_keys; c++) {
                        if (current->children[c] != nullptr) {
                            q.push(current->children[c]);
                        }
                    }
                }
            }

            std::cout << "\n";
        }
    }

    Node* bulk_load_helper(const std::vector<T>& arr, int start, int end) {

        if (start > end) {
            return nullptr;
        }
        int n = end - start + 1;
        if (n == 0) return nullptr;

        int mid1_idx = start + (n - 1) / 3;
        int mid2_idx = start + (2 * n) / 3;

        Node* node = new Node(false);
        node->keys[0] = arr[mid1_idx];
        node->num_keys = 1;

        if (mid2_idx > mid1_idx && mid2_idx <= end) {
            node->keys[1] = arr[mid2_idx];
            node->num_keys = 2;
        }

        node->children[0] = bulk_load_helper(arr, start, mid1_idx - 1);
        node->children[1] = bulk_load_helper(arr, mid1_idx + 1, mid2_idx - 1);

        if (node->num_keys == 2) {
            node->children[2] = bulk_load_helper(arr, mid2_idx + 1, end);
        }

        if (node->children[0] == nullptr && node->children[1] == nullptr && node->children[2] == nullptr) {
            node->is_leaf = true;
        }
        return node;

    }

    /**
     * @brief Recursive helper for Q4 RANGE command.
     *
     * Performs a pruned in-order traversal.
     */
    void print_range_helper(Node* node, T key_L, T key_R, bool& found_one) {
        if (node == nullptr) return;

        int i = 0;
        while (i < node->num_keys) {
            // 1. Recurse on child[i] if L is smaller than key[i]
            if (key_L < node->keys[i]) {
                if (!node->is_leaf) {
                    print_range_helper(node->children[i], key_L, key_R, found_one);
                }
            }

            // 2. Check and print key[i]
            // If key is past the range, we can stop
            if (node->keys[i] > key_R) {
                return;
            }
            // If key is in range [L, R]
            if (!(node->keys[i] < key_L)) { // Handles (key_L <= node->keys[i])
                std::cout << node->keys[i] << "\n";
                found_one = true;
            }

            i++;
        }

        // 3. Recurse on last child (children[i])
        // if R is >= the last key in this node
        if (!(key_R < node->keys[i - 1])) {
            if (!node->is_leaf) {
                print_range_helper(node->children[i], key_L, key_R, found_one);
            }
        }
    }


public:
    Tree234() : root(nullptr) {}

    void insert(T key) {
        if (root == nullptr) {
            root = new Node(true);
            root->keys[0] = key;
            root->num_keys = 1;
            return;
        }

        if (root->num_keys == 3) {
            bool was_leaf = root->is_leaf;

            // This is a valid in-place root split
            T left = root->keys[0];
            T right = root->keys[2];
            T mid = root->keys[1];

            Node* left_node = new Node(was_leaf);
            Node* right_node = new Node(was_leaf);
            left_node->keys[0] = left;
            right_node->keys[0] = right;
            left_node->num_keys = 1;
            right_node->num_keys = 1;

            left_node->children[0] = root->children[0];
            left_node->children[1] = root->children[1];
            right_node->children[0] = root->children[2];
            right_node->children[1] = root->children[3];

            root->keys[0] = mid;
            root->num_keys = 1;
            root->is_leaf = false;
            root->children[0] = left_node;
            root->children[1] = right_node;
            root->children[2] = nullptr;
            root->children[3] = nullptr;
        }

        // Now, call the helper to insert into a non-full node
        insert_into_non_full(root, key);
    }

    /**
     * @brief MODIFIED find() for Q2 and Q4.
     *
     * Returns a pointer to the T object in the tree, or nullptr if not found.
     * This allows Q2's FIND (check != nullptr) and Q4's GET (read val).
     */
    T* find(T key_obj) {
        Node* cur = root;
        while (cur) {
            int i = 0;
            // Find first key >= key_obj
            while (i < cur->num_keys && key_obj > cur->keys[i]) {
                i++;
            }

            // Check for match
            if (i < cur->num_keys && key_obj == cur->keys[i]) {
                return &cur->keys[i]; // Found
            }

            // Not found, descend
            if (cur->is_leaf) {
                return nullptr;
            }
            cur = cur->children[i];
        }
        return nullptr;
    }

    void printIn() {
        if (root == nullptr) {
            cout << "EMPTY\n";
            return;
        }
        printInorder_helper(root);
        cout << "\n";
    }

    void printLevel() {
        if (root == nullptr) {
            std::cout << "EMPTY\n";
            return;
        }
        printLevelOrder_helper(root);
    }

    void delete_node(T key) {
        if (root == nullptr) {
            // Per assignment, "If absent, ignore."
            return;
        }

        delete_helper(root, key);

        //case when the root becomes empty
        if (root != nullptr && root->num_keys == 0 && !root->is_leaf) {
            Node* old_root = root;
            root = root->children[0];
            delete old_root;
        } else if (root != nullptr && root->num_keys == 0 && root->is_leaf) {
            delete root;
            root = nullptr;
        }
    }

    void bulk_load(const std::vector<T>& sorted_keys) {
        if (sorted_keys.empty()) {
            root = nullptr;
            return;
        }
        // This will destroy the old tree, which is fine for bulk_load
        root = bulk_load_helper(sorted_keys, 0, sorted_keys.size() - 1);
    }

    // --- NEW METHODS FOR Q4 ---

    /**
     * @brief Implements Q4 'PUT key val' (Insert or Update) [cite: 142, 144]
     */
    void put(T obj) {
        T* existing = find(obj);
        if (existing) {
            // Update
            *existing = obj;
        } else {
            // Insert
            insert(obj);
        }
    }

    /**
     * @brief Implements Q4 'RANGE L R' [cite: 146]
     */
    void print_range(T key_L, T key_R) {
        if (root == nullptr) {
            std::cout << "EMPTY\n";
            return;
        }
        bool found_one = false;
        print_range_helper(root, key_L, key_R, found_one);
        if (!found_one) {
            std::cout << "EMPTY\n";
        }
    }

};

