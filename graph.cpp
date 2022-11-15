#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <list>
#include <limits>
using namespace std;
 
struct Edge {
    int src, dest;
};

class Vertex {	
	public:
		vector<int> adjList;
		int id;
		int label;
		int color;

		Vertex(){
		
		}

		Vertex(int i, vector<int> const &a) {
			id = i;
			adjList = a;
		}

		void addEdge(int to) {
			adjList.push_back(to);	
		}

		void setLabel(int l) {
			label = l;
		}

		void setColor(int c) {
			color = c;
		}

		vector<int> getAdjList() const{
			return adjList;
		}

		int getId() const {
			return id;
		}

		int getLabel() const {
			return label;
		}

		int getColor() const {
			return color;
		}
};
 
class Graph
{
	public:
 		int nrVtcs;	
		vector<Vertex> vertices;
	
    		Graph(vector<Edge> const &edges, int n)
    		{
        		vertices.resize(n);
			nrVtcs = n;
		       	for(int i = 0; i < n; i++){
				vector<int> y;
				Vertex n(i, y);
				vertices[i] = n;
			}	
       		 	for (auto &edge: edges)
        		{
            			vertices[edge.src].addEdge(edge.dest);
            			vertices[edge.dest].addEdge(edge.src);
        		}
    		}

		void addVertex(){
			vertices.resize(nrVtcs + 1);
			vector<int> y;
			Vertex vtx(nrVtcs, y);
			vertices[nrVtcs] = vtx;
			nrVtcs++;
		}

    		void addEdge(int src, int dest){
			if (src <= nrVtcs && dest <= nrVtcs){
				vertices[src].addEdge(dest);
				vertices[dest].addEdge(src);
			} else {
				cout << "Invalid vertex";
				cout << endl;
			}
    		}

		vector<Vertex> getVertices() const{
			return vertices;
		}

		int getNrVtcs() const{
			return nrVtcs;
		}

		Vertex getVertex(int id) const{
			return vertices[id];
		}

		bool isConnected(){
			return true;
		}

		bool canReach(int from, int to){
			map<int, bool> visited;
			return BFS(from, to, visited);
//			return DFS(from, to, visited);
		}

		bool DFS(int from, int to, map<int, bool> visited){
			visited[from] = true;
			vector<int> fromAdjList = vertices[from].getAdjList();
			for(int i : fromAdjList) {
				if (i == to) {
					return true;
				} else if (!visited.count(i)){
					return DFS(i, to, visited);
				}
			}
			return false;
		} 

		bool BFS(int from, int to, map<int, bool> visited){
			visited[from] = true;
			list<int> queue;
			queue.push_back(from);
		       	while(!queue.empty()){
				int from = queue.front();
				queue.pop_front();
				if (from == to){
					return true;
				}
				vector<int> adjList = vertices[from].getAdjList();
				for(int i : adjList){
					if(!visited.count(i)){
						visited[i] = true;
						queue.push_back(i);
					}
				}
			}
			return false;
		}

		int shortestPath(int from, int to) { // Dijkstra algo
			vector<int> dist;
			dist.resize(nrVtcs);
			map<int, bool> prev;
			vector<int> q;
			for (int i = 0; i < nrVtcs; i++){
				dist[i] = numeric_limits<int>::max();
				prev[i] = false;
				q.push_back(i);
			}
			dist[from] = 0;
			while (!q.empty()){
				int closestVtxId = -1;
				for (int el : q){
					if (closestVtxId < 0){
						closestVtxId = el;
					}
					else if (dist[el] <  dist[closestVtxId]) {
						closestVtxId = el;
					} 
				}
				q.erase(remove(q.begin(), q.end(), closestVtxId), q.end());
				Vertex vtx = getVertex(closestVtxId);
				for (int neighbour : vtx.getAdjList()){
					int new_dist = dist[closestVtxId] + 1; // replace with weight when implemented
					if (new_dist < dist[neighbour]) {
						dist[neighbour] = new_dist;
					}
				}
			}
			return dist[to];
		}
		
};
 
void printGraph(Graph const &graph)
{
	int n = graph.getNrVtcs();
    	for (int i = 0; i < n; i++)
    	{
        	cout << i << " ——> ";
 
		for (int v: graph.vertices[i].getAdjList()) {
        	    cout << v << " ";
        	}
        	cout << endl;
    	}
}
 
int main()
{
    vector<Edge> edges =
    {
        {0, 1}, {1, 2}, {2,3}, {3,4}, {4, 5}, {1,3}
    };
    int n = 6;
    Graph graph(edges, n);
    cout << graph.shortestPath(0,5) << endl;
 //   printGraph(graph);
 //   graph.addVertex();
 //   graph.addEdge(8,1);
 //   printGraph(graph);
 //   cout << graph.canReach(0,5) << endl;
 //   graph.addEdge(0,5);
 //   cout << graph.canReach(0,5) << endl;
    return 0;
}
