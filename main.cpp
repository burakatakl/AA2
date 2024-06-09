#include <iostream>
#include <vector>
#include <stack>

const int uncolored=-1;
const int color_1=0;
const int color_2=1;
class Graph {  // Class representing the dissatisfaction among the guests as a graph
public:
    int V;
    std::vector<std::vector<int>> adj;  //here in this vector we can see neighbor list

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};
bool canBeTwoColored(const Graph &graph, std::vector<int> &colors) {
    for (int start = 0; start < graph.V; ++start) {  // Coloring the graph with two colors using non-recursive DFS
        if (colors[start] == uncolored) {
            std::stack<int> s;
            s.push(start);
            colors[start] = color_1;

            while (!s.empty()) {
                int node = s.top();
                s.pop();

                for (int neighbor : graph.adj[node]) {
                    if (colors[neighbor] == uncolored) {
                        colors[neighbor] = 1 - colors[node];
                        s.push(neighbor);
                    } else if (colors[neighbor] == colors[node]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
void printSeatingArrangement(const std::vector<int> &colors) {
    std::cout << "Table 1: ";
    for (int i = 0; i < colors.size(); ++i) {
        if (colors[i] == color_1) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl << "Table 2: ";
    for (int i = 0; i < colors.size(); ++i) {
        if (colors[i] == color_2) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}
int main() {
    int numGuests, numDislikes;
    std::cout << "How many guess will be there  : ";
    std::cin >> numGuests;
    std::cout << "How much guess they are bad each other? : ";
    std::cin >> numDislikes;

    Graph graph(numGuests);
    std::cout << "Enter disgruntled couples (0 to " << numGuests - 1 << " ):" << std::endl;
    for (int i = 0; i < numDislikes; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.addEdge(u, v);
    }
    std::vector<int> colors(numGuests, uncolored);
    if (canBeTwoColored(graph, colors)) {
        std::cout << "Two separate table layouts can be created." << std::endl;
        printSeatingArrangement(colors);
    } else {
        std::cout << "Two separate table layouts cannot be created." << std::endl;
    }
    return 0;
}
