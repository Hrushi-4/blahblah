#include <iostream>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <fstream>
#include <queue>

using namespace std;

#define VERTEX 100
#define INPUT  "9.txt"			//Input File
#define OUTPUT "ffdeltascaling_output.txt"	//Output File

//Function Definitions
bool path_finder(int residual[VERTEX][VERTEX], int s, int t, int parent[]);   //Used for path finding
void mincut_finder(vector<vector<int> >& residual, int s, bool visited2[]);     //Used for min cut
void max_flow(int graph[VERTEX][VERTEX], int source, int sink);                //Ford Fulkerson implementation
void print_mincut(int graph[VERTEX][VERTEX], bool visited2[], int s, int t);  //Print edges of the min cut
void update_deltares(int deltares[VERTEX][VERTEX], int residual[VERTEX][VERTEX], int delta);
			    
int main()
{
    freopen(OUTPUT, "w", stdout);
    std::ifstream ifptr(INPUT, std::ifstream::in);

    int graph[VERTEX][VERTEX];
    for(int i = 0; i < VERTEX; i++)
	for( int j = 0; j < VERTEX; j++)
		graph[i][j] = 0;

    int m, n, v1, v2, c;
    if ( ifptr.is_open() )
    {
	ifptr >> m; ifptr >> n;
    
	while( !ifptr.eof() )
	{
		ifptr >> v1; ifptr >> v2; ifptr >> c;
		graph[v1][v2] = c;
	}
    }

    bool visited[VERTEX];
    memset(visited, false, sizeof(visited));

// Define the residual graph
vector<vector<int> > residual(n, vector<int>(n, 0));

// Initialize the source and sink nodes
int s = 0; // Source node
int t = n - 1; // Sink node

 
    //DFS to mark vertices which are reachable
    mincut_finder(residual, s, visited);
 
    //Printing edges in minimum cut
    cout << "\n\n \t \t MIN CUT\n";
    cout << "\t \t ____ ___\n \n"; 
    print_mincut(graph, visited, s, t);
}
 
// Returns true if there is a path from source 's' to sink 't' in residual graph.
// Also fills parent[] to store the path
bool path_finder(int residual[VERTEX][VERTEX], int s, int t, int parent[])
{
    bool visited[VERTEX];
    memset(visited, 0, sizeof(visited));
 
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    //Standard BFS loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        for (int v = 0; v < VERTEX; v++)
        {
            if (visited[v] == false && residual[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    //If sink reached return true else false
    return (visited[t] == true);
}
 
//DFS function to mark reachable vertices in given graph
void mincut_finder(vector<vector<int> >& residual, int s, bool visited2[]) {
    // BFS to find reachable vertices from s
    queue<int> q;
    q.push(s);
    visited2[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < residual[u].size(); v++) {
            if (residual[u][v] > 0 && !visited2[v]) {
                visited2[v] = true;
                q.push(v);
            }
        }
    }
}

 
//Print edges of minimum cut
void print_mincut(vector<vector<int> >& graph, bool visited[], int s, int t) {
    // Print the edges between reachable and unreachable vertices
    for (int u = 0; u < graph.size(); u++) {
        for (int v = 0; v < graph[u].size(); v++) {
            if (visited[u] && !visited[v] && graph[u][v]) {
                cout << u << " - " << v << endl;
            }
        }
    }
}

//Update Delta Residual Graph
void update_deltares(int deltares[VERTEX][VERTEX], int residual[VERTEX][VERTEX], int delta)
{
	for(int i = 0; i < VERTEX; i++)
		for(int j = 0; j < VERTEX; j++)
			if(residual[i][j] >= delta)
				deltares[i][j] = residual[i][j] - delta;
			else
				deltares[i][j] = 0;
}

