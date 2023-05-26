#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
int INT_MAX = 2147483647;

using namespace std;

// A directed and weighted graph.
class Graph {
public:
  // The number of vertices in the graph.
  int numVertices;

  // The adjacency list, where each adjacency list stores the vertices that are
  // connected to the current vertex, along with the weight of the edge.
  vector<vector<pair<int, int>>> adjacencyList;

  // Constructs a graph with the given number of vertices.
  Graph(int numVertices) {
    this->numVertices = numVertices;
    adjacencyList.resize(numVertices);
  }

  // Adds an edge between the given vertices, with the given weight.
  void addEdge(int u, int v, int weight) {
    adjacencyList[u].push_back({v, weight});
  }

  // Prints the graph.
  void print() {
    for (int i = 0; i < numVertices; i++) {
      cout << "Vertex " << i << ": ";
      for (auto edge : adjacencyList[i]) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
      }
      cout << endl;
    }
  }
  // recorrido dfs
  void dfs(int u) {
  // Create a boolean array to keep track of which vertices have been visited.
  bool *visited = new bool[numVertices];
  for (int i = 0; i < numVertices; i++) {
    visited[i] = false;
  }

  // Mark the current vertex as visited.
  visited[u] = true;

  // Recursively visit all the vertices that are
  // connected to the current vertex.
  for (auto edge : adjacencyList[u]) {
    if (!visited[edge.first]) {
      dfs(edge.first);
    }
  }

  // Print the traversal.
  for (int i = 0; i < numVertices; i++) {
    if (visited[i]) {
      cout << i << " ";
    }
  }

  // Delete the visited array.
  delete[] visited;
}
  // 

 void deleteEdge(int u, int v) {
  // Find the edge between u and v.
  auto it = std::find_if(adjacencyList[u].begin(), adjacencyList[u].end(), [&](const pair<int, int>& edge) {
    return edge.first == v;
  });

  // If the edge is found, delete it.
  if (it != adjacencyList[u].end()) {
    adjacencyList[u].erase(it);
  }
}

 void deleteVertex(int u) {
  // Remove all edges that are connected to u.
  for (auto& edge : adjacencyList[u]) {
    deleteEdge(edge.first, u);
  }

  // Remove u from the adjacency lists of all other vertices.
  for (int i = 0; i < numVertices; i++) {
    if (i != u) {
      auto it = std::find_if(adjacencyList[i].begin(), adjacencyList[i].end(), [&](const pair<int, int>& edge) {
        return edge.first == u;
      });

      if (it != adjacencyList[i].end()) {
        adjacencyList[i].erase(it);
      }
    }
  }

  // Decrease the number of vertices in the graph.
  numVertices--;
}
 bool hasPath(int u, int v) {
  // Mark all vertices as unvisited.
  bool *visited = new bool[numVertices];
  for (int i = 0; i < numVertices; i++) {
    visited[i] = false;
  }

  // Create a stack to store the vertices that are being visited.
  std::stack<int> stack;

  // Push the source vertex onto the stack.
  stack.push(u);

  // While the stack is not empty, do the following:
  while (!stack.empty()) {
    // Pop the top vertex off the stack.
    int currentVertex = stack.top();
    stack.pop();

    // If the current vertex is the destination vertex, then return true.
    if (currentVertex == v) {
      return true;
    }

    // Mark the current vertex as visited.
    visited[currentVertex] = true;

    // Iterate over all the vertices that are connected to the current vertex.
    for (auto& edge : adjacencyList[currentVertex]) {
      // If the vertex is not visited, then push it onto the stack.
      if (!visited[edge.first]) {
        stack.push(edge.first);
      }
    }
  }

  // If the stack is empty, then return false.
  return false;
}

 void floydWarshall() {
  // Create a distance matrix to store the shortest paths between all pairs of vertices.
  int **distance = new int *[numVertices];
  for (int i = 0; i < numVertices; i++) {
    distance[i] = new int[numVertices];
    for (int j = 0; j < numVertices; j++) {
      if (i == j) {
        distance[i][j] = 0;
      } else if (std::find(adjacencyList[i].begin(), adjacencyList[i].end(), j) != adjacencyList[i].end()) {
        distance[i][j] = adjacencyList[i][j].second;
      } else {
        distance[i][j] = INT_MAX;
      }
    }
  }

  // Iterate over all vertices.
  for (int k = 0; k < numVertices; k++) {
    // Iterate over all vertices.
    for (int i = 0; i < numVertices; i++) {
      // Iterate over all vertices.
      for (int j = 0; j < numVertices; j++) {
        // Update the distance between i and j if the distance between i and k plus the distance between k and j is less than the distance between i and j.
        if (distance[i][k] + distance[k][j] < distance[i][j]) {
          distance[i][j] = distance[i][k] + distance[k][j];
        }
      }
    }
  }

  // Print the distance matrix.
  for (int i = 0; i < numVertices; i++) {
    for (int j = 0; j < numVertices; j++) {
      cout << distance[i][j] << " ";
    }
    cout << endl;
  }
}
};

int main() {
  // Create a graph with 5 vertices.
  Graph graph(5);

  // Add some edges to the graph.
  graph.addEdge(0, 1, 10);
  graph.addEdge(0, 2, 20);
  graph.addEdge(1, 3, 30);
  graph.addEdge(2, 4, 40);
  

  // Print the graph.
  graph.print();
  cout<< "Recorrido dfs"<<endl;
  graph.dfs(0);
  graph.floydWarshall();

  

  return 0;
};