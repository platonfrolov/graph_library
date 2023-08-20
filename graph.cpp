#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <list>
#include <limits>
using namespace std;
 
struct Edge {
    int src, dest, weight;
};

 
class Graph
{
	public:
 		int nrVtcs;	
		vector<Edge> edges;
		vector<list<int>> adjLists;   
    	Graph(vector<Edge> const &edges, int n)
    		{
				nrVtcs = n;
				adjLists.resize(n);	
       			for (auto &edge: edges) {
						this->edges.push_back(edge);
						adjLists[edge.src].push_back(edge.dest);
						adjLists[edge.dest].push_back(edge.src);
					}
    		}

		void addVertex(){
			adjLists.resize(nrVtcs + 1);
		
			nrVtcs++;
		}

    	void addEdge(int src, int dest, int weight) {
			if (src <= nrVtcs && dest <= nrVtcs) {
				Edge newEdge = {src, dest, weight};
				this->edges.push_back(newEdge);
				adjLists[newEdge.src].push_back(newEdge.dest);
				adjLists[newEdge.dest].push_back(newEdge.src);
			} else {
				cout << "Invalid vertex";
				cout << endl;
			}
    	}


		int getNrVtcs() const{
			return nrVtcs;
		}

		bool isConnected(){
			return true;
		}

		bool isBipartite() {
			map<int, int> visited;
			int start_label = 0;
			map<int, int> vertex_labels;
			int start_vtx = 0;
			list<tuple<int, int>> queue;
			tuple<int, int> to_push = {start_vtx, start_label};
			queue.push_back(to_push);
			while (!queue.empty()) {
				tuple<int, int> front = queue.front();
				int curr = get<0>(front);
				int label = get<1>(front);
				queue.pop_front();
				if (vertex_labels.count(curr) && vertex_labels[curr] != label) {
					return false;
					
				} else {
					vertex_labels[curr] = label;
				}
				list<int> adjList = this->adjLists[curr];
				for(int i : adjList){
					if(!visited.count(i)){
						visited[i] = 1;
						tuple<int, int> to_push = {i, (label+1) % 2};
						queue.push_back(to_push);
					} else if (visited[i] == 1) {
						visited[i] = 2;
						tuple<int, int> to_push = {i, (label+1) % 2};
						queue.push_back(to_push);
					}
				}
			}
			return true;
		}

		bool canReach(int from, int to){
			return BFS(from, to);
			
		}

		bool DFS(int from, int to, map<int, bool> visited){
			visited[from] = true;
			list<int> fromAdjList = this->adjLists[from];
			bool x = false;
			for(int i : fromAdjList) {
				if (i == to) {
					return true;
				} else if (!visited.count(i)){
					x = x || DFS(i, to, visited);
				}
			}
			return x;
		} 

		bool BFS(int from, int to){
			map<int, bool> visited;
			visited[from] = true;
			list<int> queue;
			queue.push_back(from);
		       	while(!queue.empty()){
				int from = queue.front();
				queue.pop_front();
				if (from == to){
					return true;
				}
				list<int> adjList = this->adjLists[from];
				for(int i : adjList){
					if(!visited.count(i)){
						visited[i] = true;
						queue.push_back(i);
					}
				}
			}
			return false;
		}

		// int shortestPath(int from, int to) { // Dijkstra algo
		// 	vector<int> dist;
		// 	dist.resize(nrVtcs);
		// 	map<int, bool> prev;
		// 	vector<int> q;
		// 	for (int i = 0; i < nrVtcs; i++){
		// 		dist[i] = numeric_limits<int>::max();
		// 		prev[i] = false;
		// 		q.push_back(i);
		// 	}
		// 	dist[from] = 0;
		// 	while (!q.empty()){
		// 		int closestVtxId = -1;
		// 		for (int el : q){
		// 			if (closestVtxId < 0){
		// 				closestVtxId = el;
		// 			}
		// 			else if (dist[el] <  dist[closestVtxId]) {
		// 				closestVtxId = el;
		// 			} 
		// 		}
		// 		q.erase(remove(q.begin(), q.end(), closestVtxId), q.end());
		// 		Vertex vtx = getVertex(closestVtxId);
		// 		for (int neighbour : vtx.getAdjList()){
		// 			int new_dist = dist[closestVtxId] + 1; // replace with weight when implemented
		// 			if (new_dist < dist[neighbour]) {
		// 				dist[neighbour] = new_dist;
		// 			}
		// 		}
		// 	}
		// 	return dist[to];
		// }
		
		
		
		// Graph mst() {
			
		// }
		
};
 
void printGraph(Graph const &graph)
{
	int n = graph.getNrVtcs();
    	for (int i = 0; i < n; i++)
    	{
        	cout << i << " ——> ";
 
			for (int v: graph.adjLists[i]) {
        	    cout << v << " ";
        	}
        	cout << endl;
    	}
}
 
int main()
{
    vector<Edge> edges =
    {
        {0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 0, 1}, {3,4, 1}, {4, 5, 1}, {1,4,1}
    };
    int n = 6;
    Graph graph(edges, n);
    // cout << graph.shortestPath(0,5) << endl;
   	printGraph(graph);
    // graph.addVertex();
 	// // graph.addEdge(8,1,1);
	// graph.addEdge(6,1,1);
	// printGraph(graph);
   	// cout << graph.canReach(0,5) << endl;
   	// graph.addEdge(3,5,1);
   	// cout << graph.canReach(0,5) << endl;
	cout << graph.isBipartite() << endl;
    return 0;
}
