#include <bits/stdc++.h>
#include <unistd.h>
#include <thread>

using namespace std;

// Graph class represents a directed graph
// using adjacency list representation
class Graph {
public:
	map<int, bool> visited;
	map<int, list<int> > adj;

	// function to add an edge to graph
	void addEdge(int v, int w);
    void edgeDelete(int v, int w);
    void deleteNode(int v);
    void unmark(int v);
	// DFS traversal of the vertices
	// reachable from v
    void performDFS(int v);
	void DFS(int v);
};

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

void Graph::edgeDelete(int v, int w)
{
    // Find the vertex v in the adjacency list
    auto it = adj.find(v);
    if (it != adj.end()) {
        // Find the edge w in the list of vertex v
        list<int>& edges = it->second;
        edges.remove(w);
    }
}

void Graph::deleteNode(int v)
{
    // Delete the edges connected to the node v
    adj.erase(v);

    // Delete v from the adjacency lists of other nodes
    for (auto& kv : adj) {
        list<int>& edges = kv.second;
        edges.remove(v);
    }
}

void Graph::performDFS(int v)
{
    // Mark the current node as visited and
    // print it
    visited[v] = true;
    cout << v << " ";

    // Recur for all the vertices adjacent
    // to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            performDFS(*i);
}

void Graph::DFS(int v)
{
    // Clear visited map
    visited.clear();

    // Create a thread for DFS traversal
    thread dfsThread(&Graph::performDFS, this, v);

    // Wait for the DFS traversal thread to finish
    dfsThread.join();
}


void Graph::unmark(int v)
{
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if(visited[*i]){
            visited[*i] = false;
            unmark(*i);
        }
}

// Driver's code
int main()
{
	// Create a graph given in the above diagram
	Graph g;
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	// Function call
    int node;
    cout<<"\n From 2: ";
	g.DFS(2);
    g.unmark(2);
    cout<< "\nEnter node to remove\n";
    cin>>node;
    g.deleteNode(node);
    
    cout<<"\n From 0: ";
    g.DFS(0);
    g.unmark(0);
    cout<<"\n From 1: ";  
    g.DFS(1);
    g.unmark(1);
    cout<<"\n From 2: ";  
    g.DFS(2);
    g.unmark(2);
    cout<<"\n From 3: ";  
    g.DFS(3);
    g.unmark(3);

	return 0;
}

// improved by Vishnudev C
