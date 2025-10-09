#ifndef DSA_LAB_FILES_BST_H
#define DSA_LAB_FILES_BST_H

#include <iostream>
#include "P-3/queue_LL.h"
using namespace std;

template <typename T>
class BST{
private:
    struct Node{
        T key;
        Node* left;
        Node* right;
    };
    Node* root;
    Node* insert_rec_helper(T x, Node* r){
        if(r == nullptr) return new Node{x, nullptr, nullptr};
        else if(r->key > x) r->left = insert_rec_helper(x, r->left);
        else if(r->key < x) r->right = insert_rec_helper(x, r->right);
        // no insertion for duplicates
        return r;
    }
    void inorder_traverse_helper(Node* r){
        if(r == nullptr) return;
        else {
            inorder_traverse_helper(r->left);
            cout << r->key << ' ';
            inorder_traverse_helper(r->right);
        }
    }
    void postorder_traverse_helper(Node* r){
        if(r == nullptr) return;
        else {
            postorder_traverse_helper(r->left);
            postorder_traverse_helper(r->right);
            cout << r->key << ' ';
        }
    }
    void preorder_traverse_helper(Node* r){
        if(r == nullptr) return;
        else {
            cout << r->key << ' ';
            preorder_traverse_helper(r->left);
            preorder_traverse_helper(r->right);
        }
    }
    int height(Node* r){
        if(r == nullptr) return -1;                                 //height of nullptr is -1 defined
        else return 1+max(height(r->left),height(r->right));
    }

    int depth_helper(Node* cur, Node* target, int depth){
        if(cur == nullptr) return -1;
        if(cur == target) return depth;
        int x = depth_helper(cur->left,target,depth+1);
        if(x!=-1) return x;
        else return depth_helper(cur->right,target,depth+1);
    }
    int depth(Node* r){
        return depth_helper(root,r,0);
    }

    void print_depths_helper(Node* r, int cur_depth){
        if(r == nullptr) return;
        else{
            cout<<r->key<<'\t'<<cur_depth<<'\n';
            print_depths_helper(r->left,cur_depth+1);
            print_depths_helper(r->right,cur_depth+1);
        }
    }

    /*
    void print_heights_helper(Node* r, int cur_height){
        if(r==nullptr) return;
        else{
            print_heights_helper(r->left,cur_height-1);
            print_heights_helper(r->right,cur_height-1);
            cout<<r->key<<'\t'<<cur_height<<'\n';
        }
    }
     FLAWED since height of BOTH children is NOT height(parent)-1. */

    int print_heights_helper(Node* r){
        if(r == nullptr) return -1;
        else{
            int height = 1+max(print_heights_helper(r->left), print_heights_helper(r->right));
            cout<<r->key<<'\t'<<height<<'\n';
            return height;
        }
    }

    //review!!
    bool is_bst_helper(Node* current, Node* &prev){
        if(current == nullptr) return true;
        if(is_bst_helper(current->left, prev) == false) {
            return false;
        }
        if(prev != nullptr && current->key <= prev->key) return false;
        prev = current;
        return is_bst_helper(current->right,prev);
    }

    int no_of_leaves_helper(Node* r){
        if(r == nullptr) return 0;
        if(r->left == nullptr && r->right == nullptr) return 1;
        return no_of_leaves_helper(r->left)+ no_of_leaves_helper(r->right);
    }

    int calcDiameter_helper(Node* r, int& diameter){
        if(!r) return 0;
        int leftHeight = calcDiameter_helper(r->left,diameter);
        int rightHeight = calcDiameter_helper(r->right,diameter);
        diameter = max(diameter, leftHeight + rightHeight);
        return max(leftHeight, rightHeight)+1;
    }

    static Node* buildTreePreIn_help(unordered_map<T,int>& index_map, const vector<T>& preorder, int start, int end, int& preorderIndex){
        if(start>end) return nullptr;
        int rootval = preorder[preorderIndex++];
        Node* r = new Node{rootval, nullptr, nullptr};
        int inIndex = index_map[rootval];
        r->left = buildTreePreIn_help(index_map,preorder,start,inIndex-1,preorderIndex);
        r->right = buildTreePreIn_help(index_map,preorder,inIndex+1,end,preorderIndex);
        return r;
    };

    static Node* buildTreePostIn_help(unordered_map<T,int>& index_map, const vector<T>& postorder, int start, int end, int& postorderIndex){
        if(start>end) return nullptr;
        int rootval = postorder[postorderIndex--];
        Node* r = new Node{rootval, nullptr, nullptr};
        int inIndex = index_map[rootval];
        r->right = buildTreePostIn_help(index_map,postorder,inIndex+1,end,postorderIndex);
        r->left = buildTreePostIn_help(index_map,postorder,start,inIndex-1,postorderIndex);
        return r;
    };

public:
    BST() : root(nullptr) {}

    BST(Node* r) : root(r) {}

    void insert(T x){
        if(root == nullptr) {root = new Node{x, nullptr, nullptr}; return;}
        Node* temp = root;
        while(true){
            if(temp->key > x){
                if(temp->left != nullptr) temp = temp->left;
                else {temp->left = new Node{x, nullptr, nullptr}; return;}          // create a new node by dynamic memory allocation. cannot do temp->left->key since that would lead to a segfault.
            }
            else if(temp->key < x){
                if(temp->right != nullptr) temp = temp->right;
                else {temp->right = new Node{x, nullptr, nullptr}; return;}
            }
            // no insertion for duplicates
            else break;
        }
    }

    void insert_rec(T x){
        root = insert_rec_helper(x, root);      //uses private helper function
    }

    void inorder_traverse(){
        inorder_traverse_helper(root); cout<<'\n';
    }

    void postorder_traversal(){
        postorder_traverse_helper(root); cout<<'\n';
    }

    void preorder_traversal(){
        preorder_traverse_helper(root); cout<<'\n';
    }

    int height() {return height(root);}

    void print_depths() { print_depths_helper(root,0);}

    void print_heights() { print_heights_helper(root);}

    bool search(T x){
        Node* temp = root;
        while(temp != nullptr){
            if(temp->key == x) return true;
            else if(temp->key > x) temp = temp->left;
            else if(temp->key < x) temp = temp->right;
        }
        return false;
    }

    T minim(){
        if (root == nullptr) {cout<<"Empty tree"; return T();}
        else{
            Node *temp = root;
            while(temp->left != nullptr) temp = temp->left;
            return temp->key;
        }
    }

    T maxim(){
        if (root == nullptr) {cout<<"Empty tree"; return T();}
        else{
            Node *temp = root;
            while(temp->right != nullptr) temp = temp->right;
            return temp->key;
        }
    }

    void delete_node(T x){
        Node* parent = nullptr; Node* child = root;
        while(child != nullptr){
            if(child->key == x){
                //leaf node
                if(child->left == nullptr && child->right == nullptr){
                    if(parent == nullptr) { root = nullptr; }
                    else{
                        if(parent->key > x){
                            parent->left = nullptr;
                        }
                        else{
                            parent->right = nullptr;
                        }
                    }
                    delete child; return;
                }

                //single child
                else if(child->left == nullptr ^ child->right == nullptr){
                    if(parent == nullptr) {
                        if(child->left != nullptr) root = child->left;
                        else root = child->right;
                    }
                    else{
                        if(parent->key > x){
                            if(child->left != nullptr) parent->left = child->left;
                            else parent->left = child->right;
                        }
                        else{
                            if(child->left != nullptr) parent->right = child->left;
                            else parent->right = child->right;
                        }

                    }
                    delete child; return;
                }

                // two children
                else{
                    Node* temp1 = child->right;
                    Node* temp2 = child;
                    while(temp1->left != nullptr){
                        temp2 = temp1;
                        temp1 = temp1->left;
                    }
                    child->key = temp1->key;        // copy the ios into child node
                    //single child
                    if(temp2 == child) {
                        child->right = temp1->right;
                    }
                    else{
                        temp2->left = temp1->right;
                    }
                    delete temp1;
                    return;
                }

            }

            else if(child->key > x){
                parent = child; child = child->left;
            }

            else if(child->key < x){
                parent = child; child = child->right;
            }
        }
    }

    void level_order_traverse(){
        queue_LL<Node*> Q;
        if(root != nullptr){
            Q.enqueue(root);
            while(!Q.isEmpty()){
                Node* x = Q.peek();
                if(x->left != nullptr) Q.enqueue(x->left);
                if(x->right != nullptr) Q.enqueue(x->right);
                cout<<x->key<<' ';
                Q.dequeue();
            }
        }
        cout<<'\n';
    }

    bool is_bst(){
        Node* prev = nullptr;           // since prev is passed by reference, can't pass literal nullptr directly.
        return is_bst_helper(root,prev);
    }

    Node* find_successor(Node* x){
        if(x->right != nullptr){
            Node* temp = x->right;
            while(temp->left != nullptr) temp = temp->left;
            return temp;
        }
        else{
            Node* s = nullptr;
            Node* temp = root;
            while(temp != nullptr && temp != x){
                if(temp->key > x->key){
                    s = temp; temp = temp->left;
                }
                else temp = temp->right;
            }
            return s;
        }
    }

    static long long no_of_bsts(int n){
        long long catalan[n+1];
        catalan[0] = 1;
        for(int i = 1; i<=n; i++){
            catalan[i] = 0;
            for(int j = 0; j<i; j++){
                catalan[i] += catalan[j]*catalan[i-j-1];
            }
        }
        return catalan[n];
    }

    int no_of_leaves(){
        return no_of_leaves_helper(root);
    }

    int calcDiameter(){
        int diameter = 0;
        calcDiameter_helper(root,diameter);
        return diameter;
    }

    static Node* buildTreePreIn(){
        int n; cout<<"size of tree: "; cin>>n;
        cout<<"preorder: ";
        vector<T> preorder(n);
        for(T &x:preorder) cin>>x;
        unordered_map<T,int> index_map;
        cout<<"Inorder: ";
        for(int i = 0; i<n; i++){
            int x; cin>>x;
            index_map[x] = i;
        }
        int preorderIn = 0;
        Node* r = buildTreePreIn_help(index_map,preorder,0,n-1,preorderIn);
        return r;
    }

    static Node* buildTreePostIn(){
        int n; cout<<"size of tree: "; cin>>n;
        cout<<"postorder: ";
        vector<T> postorder(n);
        for(T &x:postorder) cin>>x;
        unordered_map<T,int> index_map;
        cout<<"Inorder: ";
        for(int i = 0; i<n; i++){
            int x; cin>>x;
            index_map[x] = i;
        }
        int postorderIn = n-1;
        Node* r = buildTreePostIn_help(index_map,postorder,0,n-1,postorderIn);
        return r;
    }

};

#endif //DSA_LAB_FILES_BST_H
