#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm> // Required for std::sort
#include <tuple>     // Required for std::tuple

template<typename T>
class Graph {
private:
    int V;
    std::vector<std::vector<std::pair<int, T>>> adjList;
    std::vector<std::vector<T>> adjMatrix;
    T noEdgeValue;

    // --- Helpers ---

    void DFS_rec_helper(int u, std::vector<bool>& visited, std::vector<int>& dfs_traverse) {
        visited[u] = true;
        dfs_traverse.push_back(u);

        for (auto& p : adjList[u]) {
            if (!visited[p.first]) {
                DFS_rec_helper(p.first, visited, dfs_traverse);
            }
        }
    }

    void BFS_helper(int start, std::vector<bool>& visited, std::vector<int>& bfs_traverse) {
        std::queue<int> Q;
        Q.push(start);
        visited[start] = true;

        while (!Q.empty()) {
            int cur = Q.front();
            Q.pop();
            bfs_traverse.push_back(cur);
            for (auto& p : adjList[cur]) {
                if (!visited[p.first]) {
                    Q.push(p.first);
                    visited[p.first] = true;
                }
            }
        }
    }

    // DSU Helper for Kruskal's
    struct DSU_helper {
        std::vector<int> parent;
        std::vector<int> rank;

        DSU_helper(int n) {
            parent.resize(n);
            rank.resize(n, 0); // Rank initialized to 0
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        int find(int i) {
            if (parent[i] != i)
                parent[i] = find(parent[i]); // Path Compression
            return parent[i];
        }

        void unite(int a, int b) {
            int root_a = find(a);
            int root_b = find(b);
            if (root_a != root_b) {
                // Union by Rank optimization
                if (rank[root_a] > rank[root_b]) {
                    parent[root_b] = root_a;
                } else if (rank[root_b] > rank[root_a]) {
                    parent[root_a] = root_b;
                } else {
                    parent[root_b] = root_a;
                    rank[root_a]++;
                }
            }
        }
    };

    void toposort_helper(int vertex, std::vector<bool>& visited, std::stack<int>& topo) {
        visited[vertex] = true;
        for (auto& p : adjList[vertex]) {
            if (!visited[p.first])
                toposort_helper(p.first, visited, topo);
        }
        topo.push(vertex);
    }

    bool isCyclicDirected_helper(int u, std::vector<bool>& visited, std::vector<bool>& recStack) {
        visited[u] = true;
        recStack[u] = true;

        for (auto& p : adjList[u]) {
            int v = p.first;
            if (!visited[v]) {
                if (isCyclicDirected_helper(v, visited, recStack)) return true;
            } else if (recStack[v]) {
                return true;
            }
        }
        recStack[u] = false;
        return false;
    }

    bool isCyclicUndirected_helper(int u, std::vector<bool>& visited, int parent) {
        visited[u] = true;
        for (auto& p : adjList[u]) {
            int v = p.first;
            if (!visited[v]) {
                if (isCyclicUndirected_helper(v, visited, u)) return true;
            } else if (v != parent) {       // avoiding detecting trivial cycles in undirected graph
                return true;
            }
        }
        return false;
    }

    // Helper for SCC (Kosaraju Step 1)
    void fillOrder(int u, std::vector<bool>& visited, std::stack<int>& Stack) {
        visited[u] = true;
        for (auto& p : adjList[u]) {
            if (!visited[p.first]) {
                fillOrder(p.first, visited, Stack);
            }
        }
        Stack.push(u);
    }

    // Helper for SCC (Kosaraju Step 2)
    Graph<T> getTranspose() {
        Graph<T> g_rev(V, noEdgeValue);
        for (int u = 0; u < V; u++) {
            for (auto& p : adjList[u]) {
                g_rev.addEdge(p.first, u, p.second, true); // Add reversed edge (directed)
            }
        }
        return g_rev;
    }

    // Helper for SCC (Kosaraju Step 3)
    void DFS_SCC(int u, std::vector<bool>& visited) {
        visited[u] = true;
        std::cout << u << " ";
        for (auto& p : adjList[u]) {
            if (!visited[p.first]) {
                DFS_SCC(p.first, visited);
            }
        }
    }

public:
    Graph(int vertices, T noEdgeVal) : V(vertices), noEdgeValue(noEdgeVal) {
        adjList.resize(vertices);
        adjMatrix.resize(vertices, std::vector<T>(V, noEdgeValue));
        for (int i = 0; i < V; ++i) {
            adjMatrix[i][i] = 0;
        }
    }

    void addEdge(int a, int b, T weight, bool directed = false) {
        adjList[a].push_back({b, weight});
        adjMatrix[a][b] = weight;
        if (!directed) {
            adjList[b].push_back({a, weight});
            adjMatrix[b][a] = weight;
        }
    }

    void dispAdjList() {
        std::cout << "----Adjacency List----\n";
        for (int i = 0; i < V; i++) {
            std::cout << i << " : ";
            for (auto& p : adjList[i]) {
                std::cout << "(" << p.first << "," << p.second << ") ";
            }
            std::cout << "\n";
        }
    }

    void dispAdjMatrix() {
        std::cout << "----Adjacency Matrix----\n";
        std::cout << "   ";
        for (int i = 0; i < V; ++i) std::cout << i << " ";
        std::cout << std::endl;
        for (int i = 0; i < V; ++i) std::cout << "--";
        std::cout << std::endl;

        for (int i = 0; i < V; ++i) {
            std::cout << i << "| ";
            for (int j = 0; j < V; ++j) {
                if (adjMatrix[i][j] == noEdgeValue) {
                    std::cout << "x ";
                } else {
                    std::cout << adjMatrix[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    // Q2: BFS
    std::vector<int> BFS(int source) {
        std::vector<int> bfs_traverse;
        std::vector<bool> visited(V, false);

        BFS_helper(source, visited, bfs_traverse);
        for (int i = 0; i < V; i++) {
            if (!visited[i]) BFS_helper(i, visited, bfs_traverse);
        }
        return bfs_traverse;
    }

    // Q3: Iterative DFS
    std::vector<int> DFS_iter(int source) {
        std::vector<int> dfs_traverse;
        std::vector<bool> visited(V, false);
        std::stack<int> S;
        S.push(source);
        visited[source] = true; // Mark pushed node as visited

        while (!S.empty()) {
            int cur = S.top();
            S.pop();
            dfs_traverse.push_back(cur);
            for (auto& p : adjList[cur]) {
                if (!visited[p.first]) {
                    S.push(p.first);
                    visited[p.first] = true;
                }
            }
        }
        return dfs_traverse;
    }

    // Q3: Recursive DFS
    std::vector<int> DFS_rec(int source) {
        std::vector<int> dfs_traverse;
        std::vector<bool> visited(V, false);

        DFS_rec_helper(source, visited, dfs_traverse);
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                DFS_rec_helper(i, visited, dfs_traverse);
            }
        }
        return dfs_traverse;
    }

    // Q4: Dijkstra
    std::vector<std::pair<T, int>> Dijkstra(int source) {
        std::vector<T> dist(V, std::numeric_limits<T>::max());
        std::vector<int> parent(V, -1);

        using pii = std::pair<T, int>;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            T d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto& edge : adjList[u]) {
                int v = edge.first;
                T weight = edge.second;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        std::vector<std::pair<T, int>> result(V);
        for (int i = 0; i < V; ++i) result[i] = {dist[i], parent[i]};
        return result;
    }

    // Q5: Kruskal's MST
    Graph<T> KruskalMST() {
        Graph<T> mst(V, noEdgeValue);
        std::vector<std::tuple<T, int, int>> edges;

        for (int u = 0; u < V; ++u) {
            for (auto& pair : adjList[u]) {
                int v = pair.first;
                T weight = pair.second;
                if (u < v) edges.push_back(std::make_tuple(weight, u, v));
            }
        }
        std::sort(edges.begin(), edges.end());

        DSU_helper dsu(V);
        for (auto& edge : edges) {
            T weight = std::get<0>(edge);
            int u = std::get<1>(edge);
            int v = std::get<2>(edge);

            if (dsu.find(u) != dsu.find(v)) {
                dsu.unite(u, v);
                mst.addEdge(u, v, weight, false);
            }
        }
        return mst;
    }

    // Q6: Prim's MST
    Graph<T> PrimsMST() {
        Graph<T> mst(V, noEdgeValue);
        std::vector<T> key(V, std::numeric_limits<T>::max());
        std::vector<int> parent(V, -1);
        std::vector<bool> inMST(V, false);

        using pii = std::pair<T, int>;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;

        key[0] = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;

            for (auto& edge : adjList[u]) {
                int v = edge.first;
                T weight = edge.second;
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({key[v], v});
                }
            }
        }

        for (int i = 1; i < V; ++i) {
            if (parent[i] != -1) mst.addEdge(parent[i], i, key[i], false);
        }
        return mst;
    }

    // Q7: Topological Sort
    std::vector<int> toposort() {
        std::vector<int> toposort;
        std::stack<int> sorted;
        std::vector<bool> visited(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) toposort_helper(i, visited, sorted);
        }

        while (!sorted.empty()) {
            toposort.push_back(sorted.top());
            sorted.pop();
        }

        return toposort;
    }

    // Q8: Cycle Detection
    bool isCyclicDirected() {
        std::vector<bool> visited(V, false);
        std::vector<bool> recStack(V, false);
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                if (isCyclicDirected_helper(i, visited, recStack)) return true;
            }
        }
        return false;
    }

    bool isCyclicUndirected() {
        std::vector<bool> visited(V, false);
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                if (isCyclicUndirected_helper(i, visited, -1)) return true;
            }
        }
        return false;
    }

    // Q10: Bipartite Check
    bool checkBipartiteBFS() {
        std::vector<int> colors(V, -1);

        // outer loop for handling disconnected components - runs once per connected component
        for (int i = 0; i < V; i++) {
            // if loop has run before for the connected component this i belongs to, all nodes have been colored, and colors[i] != -1, hence loop does not run
            if (colors[i] == -1) {
                // initialize the color = 0 for this component
                std::queue<int> Q;
                Q.push(i);
                colors[i] = 0;

                while (!Q.empty()) {
                    int u = Q.front();
                    Q.pop();
                    for (auto& edge : adjList[u]) {
                        int v = edge.first;
                        if (colors[v] == -1) {
                            colors[v] = 1 - colors[u];
                            Q.push(v);
                        } else if (colors[v] == colors[u]) {        // already colored under some other constraint, and that too with the same color as u - hence not bipartite
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    // Q9: SCC (Kosaraju)
    void printSCCs() {
        std::stack<int> Stack;
        std::vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) fillOrder(i, visited, Stack);      // pretty same as toposort, just populates the Stack here.
        }

        Graph<T> gr = getTranspose();
        std::fill(visited.begin(), visited.end(), false);

        std::cout << "--- Strongly Connected Components ---\n";
        while (!Stack.empty()) {
            int u = Stack.top();
            Stack.pop();
            if (!visited[u]) {
                std::cout << "SCC: ";
                gr.DFS_SCC(u, visited);
                std::cout << "\n";
            }
        }
    }
};