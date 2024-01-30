#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

struct Edge {
    int destination;
    int weight;
};

struct Node {
    int id;
    vector<Edge> neighbors;
};

class Graph {
public:
    unordered_map<int, Node> nodes;

    void addEdge(int source, int destination, int weight) {
        nodes[source].id = source;
        nodes[destination].id = destination;
        nodes[source].neighbors.push_back({destination, weight});
    }

    pair<int, vector<int>> dijkstra(int start, int end) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        unordered_map<int, int> distance;
        unordered_map<int, int> previous;

        for (const auto& pair : nodes) {
            int node = pair.first;
            distance[node] = numeric_limits<int>::max();
            previous[node] = -1;
        }

        distance[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int current = pq.top().second;
            pq.pop();

            for (const auto& neighbor : nodes[current].neighbors) {
                int new_distance = distance[current] + neighbor.weight;
                if (new_distance < distance[neighbor.destination]) {
                    distance[neighbor.destination] = new_distance;
                    previous[neighbor.destination] = current;
                    pq.push({new_distance, neighbor.destination});
                }
            }
        }

        vector<int> path;
        int current = end;
        while (current != -1) {
            path.push_back(current);
            current = previous[current];
        }

        reverse(path.begin(), path.end());

        return {distance[end], path};
    }
};

int main() {
    Graph graph;

    // You can hard code your graph data or ask the user for it
    graph.addEdge(1, 2, 5);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 4, 1);
    graph.addEdge(3, 4, 6);
    graph.addEdge(4, 5, 3);

    cout << "Enter the starting node: ";
    int start;
    cin >> start;

    cout << "Enter the ending node: ";
    int end;
    cin >> end;

    auto result = graph.dijkstra(start, end);

    cout << "Cost of the shortest path: " << result.first << endl;
    cout << "Shortest path: ";
    for (int node : result.second) {
        cout << node << " ";
    }

    return 0;
}
