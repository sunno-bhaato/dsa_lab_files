#include <iostream>
#include <vector>
#include <fstream>
#include "P-1/LL.h"
#include "P-5/BST.h"
#include "P-6/heappidu.h"
#include "P-5/sort_algos.h"
#include "P-7/AVL.h"
#include "P-8/Tree234.h"
#include "P-9/Graph.h"

using namespace std;

void test_bst() {
    cout << "=== BST Public Interface Test ===" << endl;

    BST<int> tree;

    // Insert elements
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Inorder traversal (should be sorted): ";
    tree.inorder_traverse();

    cout << "Preorder traversal: ";
    tree.preorder_traversal();

    cout << "Postorder traversal: ";
    tree.postorder_traversal();

    cout << "Level order traversal: ";
    tree.level_order_traverse();

    // Search for present and absent values
    cout << "Search 60: " << (tree.search(60) ? "Found" : "Not found") << endl;
    cout << "Search 100: " << (tree.search(100) ? "Found" : "Not found") << endl;

    // Min and max
    cout << "Minimum: " << tree.minim() << endl;
    cout << "Maximum: " << tree.maxim() << endl;

    // Height
    cout << "Height: " << tree.height() << endl;

    // Number of leaves (using public wrapper)
    cout << "Number of leaves: " << tree.no_of_leaves() << endl;

    // Diameter (using public wrapper)
    cout << "Diameter: " << tree.calcDiameter() << endl;

    // BST property check
    cout << "Is BST: " << (tree.is_bst() ? "Yes" : "No") << endl;

    // Delete leaf, one child, two children
    tree.delete_node(20); // leaf
    tree.delete_node(30); // one child
    tree.delete_node(50); // two children

    cout << "Inorder after deletions: ";
    tree.inorder_traverse();

    // Duplicate insertion
    tree.insert(40);
    cout << "Inorder after duplicate insert: ";
    tree.inorder_traverse();

    // Test static tree construction from traversals (using public static methods)
    cout << "Testing tree construction from traversals:" << endl;
    BST<int> tree_prein(BST<int>::buildTreePreIn());
    cout << "Postorder traversal (from Preorder+Inorder): ";
    tree_prein.postorder_traversal();

    BST<int> tree_postin(BST<int>::buildTreePostIn());
    cout << "Preorder traversal (from Postorder+Inorder): ";
    tree_postin.preorder_traversal();

    cout << "=== End of BST Test ===" << endl;


}

vector<vector<int>> all_possible_trees(const vector<int>& a, int start, int end){
    if(start > end) return {{}};
    vector<vector<int>> all_preorders;
    for(int i = start; i<=end; i++){
        vector<vector<int>> left_sub_pres = all_possible_trees(a,start,i-1);
        vector<vector<int>> right_sub_pres = all_possible_trees(a,i+1,end);
        for(vector<int> l:left_sub_pres){
            for(vector<int> r:right_sub_pres){
                vector<int> root = {a[i]};
                root.insert(root.end(),l.begin(),l.end());
                root.insert(root.end(),r.begin(),r.end());
                all_preorders.push_back(root);
            }
        }
    }
    return all_preorders;
}

void print(vector<int> &a){
    for(int i:a) cout<<i<<' ';
    cout<<'\n';
}

void test_LL() {
    std::cout << "=== Linked List Public Interface Test ===\n";
    LL list;

    // Test isEmpty on new list
    std::cout << "Is empty (should be true): " << (list.isEmpty() ? "Yes" : "No") << std::endl;

    // Insert at beginning
    list.insertAtBeginning(10);
    list.insertAtBeginning(20);
    list.insertAtBeginning(30);
    std::cout << "List after insertAtBeginning (30, 20, 10): ";
    list.printList();

    // Insert at end
    list.insertAtEnd(40);
    list.insertAtEnd(50);
    std::cout << "List after insertAtEnd (40, 50): ";
    list.printList();

    // Insert at index
    list.insertAtIndex(25, 2); // Insert 25 at index 2
    std::cout << "List after insertAtIndex(25, 2): ";
    list.printList();

    // Search for elements
    std::cout << "Search for 20 (should be 1): " << list.searchList(20) << std::endl;
    std::cout << "Search for 100 (should be -1): " << list.searchList(100) << std::endl;

    // Delete from beginning
    list.delFromBeginning();
    std::cout << "List after delFromBeginning: ";
    list.printList();

    // Delete from end
    list.delFromEnd();
    std::cout << "List after delFromEnd: ";
    list.printList();

    // Delete from index
    list.delFromIndex(2);
    std::cout << "List after delFromIndex(2): ";
    list.printList();

    // Delete element by value
    list.delElement(25);
    std::cout << "List after delElement(25): ";
    list.printList();

    // Sort ascending
    list.insertAtEnd(5);
    list.insertAtEnd(15);
    list.sort_asc();
    std::cout << "List after sortasc: ";
    list.printList();

    // Reverse list
    list.reverse();
    std::cout << "List after reverse: ";
    list.printList();

    // Recursive reverse
    list.reverse_recurse();
    std::cout << "List after reverse recursive: ";
    list.printList();

    // Merge with another list
    LL other;
    other.insertAtEnd(100);
    other.insertAtEnd(200);
    LL merged = list.merge(other);
    std::cout << "Merged list: ";
    merged.printList();

    std::cout << "Is empty (should be false): " << (list.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "=== End of Linked List Test ===\n";
}

void test_heap() {
    vector<int> arr = {2, 0, 7, 3, 19, 12, -12};
    Heap maheap(arr);
    maheap.printHeap();
    maheap.insert(27);
    maheap.printHeap();
    maheap.insert(-7);
    maheap.insert(9);
    maheap.insert(23);
    maheap.insert(97);
    maheap.printHeap();
    while(!maheap.isEmpty()) cout<<maheap.extractMax()<<' ';
    maheap.printHeap();
    cout<<maheap.isEmpty();
}

void test_sort() {
    vector<int> arr1 = {4,3,5,2,6,2,9,0};
    vector<int> arr2 = {3,-7,10,99,15,67,0,78,012};
    vector<int> arr3 = {4,13,0,2,3,5,2,5,8,1,0,2,3,1,90,45,23,43};
    vector<int> arr4 = {98,1,-56,34,10,23,45,97,22,1};
    vector<int> arr5 = {9,-5,-6,4,1,0,27,2,1};
    vector<int> arr6 = {45,2,7,8,10,-12,23};
    mergeSort(arr1,0,arr1.size()-1);
    quickSort(arr2,0,arr2.size()-1);
    heapSort(arr3);
    insertionSort(arr4);
    bubbleSort(arr5);
    selectionSort(arr6);
    printArray(arr1);
    printArray(arr2);
    printArray(arr3);
    printArray(arr4);
    printArray(arr5);
    printArray(arr6);
}

void test_avl() {
    AVL<int> myTree;
    std::string command;
    int key, L, R, k;
    std::string type;

    while (std::cin >> command) {
        if (command == "INSERT") {
            std::cin >> key;
            myTree.insert(key);
        } else if (command == "DELETE") {
            std::cin >> key;
            myTree.delete_node(key);
        } else if (command == "FIND") {
            std::cin >> key;
            myTree.find(key) ? cout<<"FOUND\n" : cout<<"NOT FOUND\n";
        } else if (command == "PREV") {
            std::cin >> key;
            myTree.prev(key);
        } else if (command == "NEXT") {
            std::cin >> key;
            myTree.next(key);
        } else if (command == "PRINT") {
            std::cin >> type;
            myTree.print(type);
        } else if (command == "RANGE_COUNT") {
            std::cin >> L >> R;
            std::cout << myTree.range_count(L, R) << "\n";
        } else if (command == "RANK") {
            std::cin >> key;
            myTree.rank(key);
        } else if (command == "SELECT") {
            std::cin >> k;
            myTree.select(k);
        } else if (command == "RANGE_SUM") {
            std::cin >> L >> R;
            myTree.range_sum(L, R);
        }
    }
}

void test_234(){
    Tree234<int> q2_tree;
    Tree234<KeyValue> q4_tree;

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string command;
        ss >> command;

        // --- Q2 Commands ---
        if (command == "INSERT") {
            int val;
            ss >> val;
            q2_tree.insert(val);
        } else if (command == "DELETE") {
            int val;
            ss >> val;
            q2_tree.delete_node(val);
        } else if (command == "FIND") {
            int val;
            ss >> val;
            if (q2_tree.find(val) != nullptr) {
                cout << "FOUND\n";
            } else {
                cout << "NOTFOUND\n";
            }
        } else if (command == "PRINT") {
            string type;
            ss >> type;
            if (type == "IN") {
                q2_tree.printIn();
            } else if (type == "LEVEL") {
                q2_tree.printLevel();
            }
        } else if (command == "BULK") {
            int n;
            ss >> n;
            vector<int> keys(n);
            for (int i = 0; i < n; ++i) {
                ss >> keys[i];
            }
            q2_tree.bulk_load(keys);
        }
            // --- Q4 Commands ---
        else if (command == "PUT") {
            int k, v;
            ss >> k >> v;
            q4_tree.put(KeyValue{k, v});
        } else if (command == "GET") {
            int k;
            ss >> k;
            KeyValue* result = q4_tree.find(KeyValue{k, 0});
            if (result) {
                cout << result->val << "\n";
            } else {
                cout << "NOTFOUND\n";
            }
        } else if (command == "RANGE") {
            int L, R;
            ss >> L >> R;
            q4_tree.print_range(KeyValue{L, 0}, KeyValue{R, -1}); // Value doesn't matter
        } else if (command == "BATCH_DELETE") {
            int m;
            ss >> m;
            for (int i = 0; i < m; ++i) {
                int k;
                ss >> k;
                q4_tree.delete_node(KeyValue{k, 0});
            }
        }
    }
}

void test_234_file(){
    // 1. Create an input file stream and open the file
    ifstream fin("test_input.txt");

    // 2. Check if the file opened successfully
    if (!fin.is_open()) {
        cerr << "Error: Could not open file 'test_input.txt'\n";
        cerr << "Please make sure the file is in the same directory as the executable.\n";
        return;
    }

    Tree234<int> q2_tree;
    Tree234<KeyValue> q4_tree;

    string line;
    // 3. Read from the file stream 'fin' instead of 'cin'
    while (getline(fin, line)) {
        if (line.empty() || line[0] == '#') continue; // Ignore empty lines and comments

        stringstream ss(line);
        string command;
        ss >> command;

        // --- Q2 Commands ---
        if (command == "INSERT") {
            int val;
            ss >> val;
            q2_tree.insert(val);
        } else if (command == "DELETE") {
            int val;
            ss >> val;
            q2_tree.delete_node(val);
        } else if (command == "FIND") {
            int val;
            ss >> val;
            if (q2_tree.find(val) != nullptr) {
                cout << "FOUND\n";
            } else {
                cout << "NOTFOUND\n";
            }
        } else if (command == "PRINT") {
            string type;
            ss >> type;
            if (type == "IN") {
                q2_tree.printIn();
            } else if (type == "LEVEL") {
                q2_tree.printLevel();
            }
        } else if (command == "BULK") {
            int n;
            ss >> n;
            vector<int> keys(n);
            for (int i = 0; i < n; ++i) {
                ss >> keys[i];
            }
            q2_tree.bulk_load(keys);
        }
            // --- Q4 Commands ---
        else if (command == "PUT") {
            int k, v;
            ss >> k >> v;
            q4_tree.put(KeyValue{k, v});
        } else if (command == "GET") {
            int k;
            ss >> k;
            KeyValue* result = q4_tree.find(KeyValue{k, 0});
            if (result) {
                cout << result->val << "\n";
            } else {
                cout << "NOTFOUND\n";
            }
        } else if (command == "RANGE") {
            int L, R;
            ss >> L >> R;
            q4_tree.print_range(KeyValue{L, 0}, KeyValue{R, -1}); // Value doesn't matter
        } else if (command == "BATCH_DELETE") {
            int m;
            ss >> m;
            for (int i = 0; i < m; ++i) {
                int k;
                ss >> k;
                q4_tree.delete_node(KeyValue{k, 0});
            }
        }
    }

    // 4. (Optional but good practice) Close the file
    fin.close();
}

void test_graph(){
    int V = 6;
    int noEdge = INT_MAX; // Represents infinity

    // ==========================================
    // TEST 1: Undirected, Weighted Graph
    // (Testing BFS, DFS, Dijkstra, MSTs, Bipartite)
    // ==========================================
    std::cout << "=================================\n";
    std::cout << "TEST SET 1: Undirected & Weighted\n";
    std::cout << "=================================\n";

    Graph<int> g1(V, noEdge);

    // Building a graph: 0-1, 0-2, 1-2, 1-3, 2-4, 3-4, 3-5, 4-5
    // Weights are arbitrary
    g1.addEdge(0, 1, 4);
    g1.addEdge(0, 2, 4);
    g1.addEdge(1, 2, 2);
    g1.addEdge(1, 3, 5); // 0 --(4)--> 1 --(5)--> 3
    g1.addEdge(2, 3, 8);
    g1.addEdge(2, 4, 10);
    g1.addEdge(3, 4, 2);
    g1.addEdge(3, 5, 6);
    g1.addEdge(4, 5, 3);

    g1.dispAdjList();
    g1.dispAdjMatrix();

    // 1. BFS
    std::cout << "\n[BFS starting at 0]: ";
    vector<int> bfs = g1.BFS(0);
    for(int x : bfs) cout << x << " ";
    cout << endl;

    // 2. DFS (Recursive)
    std::cout << "[DFS Recursive at 0]: ";
    vector<int> dfs_r = g1.DFS_rec(0);
    for(int x : dfs_r) cout << x << " ";
    cout << endl;

    // 3. DFS (Iterative)
    std::cout << "[DFS Iterative at 0]: ";
    vector<int> dfs_i = g1.DFS_iter(0);
    for(int x : dfs_i) cout << x << " ";
    cout << endl;

    // 4. Dijkstra
    std::cout << "[Dijkstra Source 5]:\n";
    auto dists = g1.Dijkstra(5);
    for(int i=0; i<V; i++) {
        cout << "  Node " << i << " Dist: " << dists[i].first << " (Prev: " << dists[i].second << ")\n";
    }

    // 5. Prim's MST
    std::cout << "\n[Prim's MST]:\n";
    Graph<int> primMST = g1.PrimsMST();
    primMST.dispAdjList();

    // 6. Kruskal's MST
    std::cout << "\n[Kruskal's MST]:\n";
    Graph<int> kruskalMST = g1.KruskalMST();
    kruskalMST.dispAdjList();

    // 7. Bipartite Check (This graph has a triangle 0-1-2, so it is NOT bipartite)
    std::cout << "\n[Is Bipartite?]: " << (g1.checkBipartiteBFS() ? "Yes" : "No") << endl;


    // ==========================================
    // TEST 2: Directed Graph (DAG & Cyclic)
    // (Testing Topo Sort, Cycle Detection, SCC)
    // ==========================================
    std::cout << "\n\n=================================\n";
    std::cout << "TEST SET 2: Directed\n";
    std::cout << "=================================\n";

    // Graph for Topological Sort (DAG)
    // 5->0, 5->2, 4->0, 4->1, 2->3, 3->1
    Graph<int> g2(6, noEdge);
    g2.addEdge(5, 0, 1, true);
    g2.addEdge(5, 2, 1, true);
    g2.addEdge(4, 0, 1, true);
    g2.addEdge(4, 1, 1, true);
    g2.addEdge(2, 3, 1, true);
    g2.addEdge(3, 1, 1, true);

    std::cout << "Graph 2 (DAG):\n";
    g2.dispAdjList();
    cout<<"\n";

    // 8. Topological Sort
    cout<<"---TOPOLOGICAL SORT---\n";
    vector<int> ts = g2.toposort();
    for(int x:ts) cout<<x<<" ";
    cout<<"\n\n";

    // 9. Cycle Detection
    std::cout << "[Cycle Directed G2?]: " << (g2.isCyclicDirected() ? "Yes" : "No") << endl;

    // Create a new graph with a Cycle for SCC Test
    // 0->1, 1->2, 2->0 (Cycle 1), 1->3, 3->4
    Graph<int> g3(5, noEdge);
    g3.addEdge(0, 1, 1, true);
    g3.addEdge(1, 2, 1, true);
    g3.addEdge(2, 0, 1, true);
    g3.addEdge(1, 3, 1, true);
    g3.addEdge(3, 4, 1, true);

    std::cout << "\nGraph 3 (With Cycle):\n";
    g3.dispAdjList();
    std::cout << "[Cycle Directed G3?]: " << (g3.isCyclicDirected() ? "Yes" : "No") << endl;

    // 10. SCC (Kosaraju)
    // Should find {0,1,2} as one component, {3} as one, {4} as one.
    g3.printSCCs();
}

int main(){

//    test_bst();
//    test_LL();
//    test_heap();
//    test_sort();

//    test_234();

//    test_234_file();

//    test_graph();
    test_avl();

    return 0;
}