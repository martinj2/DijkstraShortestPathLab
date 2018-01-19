//Jennie Martin
//CSC 3430 - Tindall
//Lab 4- Implement Dijkstra Shortest Path Greedy Algorithm
/*This program implements the solution of a Dijkstra Shortest Path greedy algorithm for an undirected
weighted connected graph with no self-cycles. The solution determines the shortest-path distance and
the specific sequence of vertices that make up the shortest-path from any starting vertex in a graph
to each of the other destination vertices.*/

/*Code is adapted from GeeksForGeeks example code at
http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/ */

#include <iostream>
using namespace std;

#define V 9  //defining the number of vertices in the graph
void dijkstra(int[V][V], int); //function to do Dijkstra's algorithm
int minDistance(int dist[], bool sptSet[]); //function to find minimum distance for algorithm
void printPath(int dist[], int n, int v, int path[V]); //function to print the path and distance for each vertex


int main()
{
	int vertexNumber = 0;  //Number of the vertex that we want to analyze (initialized to 0)
	int vertexMax = V - 1; //Maximum vertex number because numbering starts at 0


	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },        //hard-coded adjacency-matrix representation of graph
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
						{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
						{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }
						};

	
	//Welcome message and input from user
	cout << endl << "\tWelcome to the Dijkstra Shortest Path Generator for Graphs!" << endl;
	cout << endl << "\tPlease enter the vertex number that you would like to start with: " << endl;
	cout << endl << "\t(If you'd like to end the program then please enter -1)" << endl;
	cin >> vertexNumber;

	while ((vertexNumber >= 0) && (vertexNumber <= vertexMax))
	{
		dijkstra(graph, vertexNumber); //call the dijkstra shortest path function
		cout << endl << "\tPlease enter the vertex number that you would like to start with: " << endl;
		cout << endl << "\t(If you'd like to end the program then please enter -1)" << endl;
		cin >> vertexNumber;
	}
	//End program message
	cout << endl << "\tThanks for using the Dijkstra Shortest Path Generator!" << endl;

	system("pause");
	return 0;
}

void dijkstra(int graph[V][V], int src) 
{

	int parentArray[V]; //holds the path information 

	for (int n = 0; n < V; n++)
		parentArray[n] = 0;			//initialize parent array to hold 0's


	int dist[V];     // The output array.  dist[i] will hold the shortest
					// distance from src to i

	bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
				   // path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;


	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++)
		{

			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
			{
				dist[v] = dist[u] + graph[u][v];

				parentArray[v] = u; //update the parentArray to keep track of u

			}
		}

	}

	parentArray[src] = src; //make sure that the current vertex only holds the current vertex for pathing

	// print the constructed distance array
	printPath(dist, V, src, parentArray);
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
	// Initialize min value
	int min = INT_MAX, minIndex;

	for (int j = 0; j < V; j++)
	if (sptSet[j] == false && dist[j] <= min)
		min = dist[j], minIndex = j;

	return minIndex;
}

// A utility function to print the constructed distance array and path information
void printPath(int dist[], int n, int v, int path[V])
{
	int tempArray[V];

	cout << endl << "\tVertex   Distance from Source:\t" << v << endl;
	for (int i = 0; i < n; i++)

	{
		int k = 0;
		cout << "\t" << i << "\t\t" << dist[i] << "\t\t Path: " << v;
		if (i == v) //if the current vertex is equal to the chosen vertex then we only want to print that vertex
			cout << endl;
		else
		{
			for (int p = 0; p < V; p++)
				tempArray[p] = v;

			for (int j = i; path[j] != v; j = path[j]) //since this logic creates a backwards array, we copy it into tempArray
			{
				tempArray[k] = path[j];
				k++;
			}
			if (k>0)
				k--;
			while ((k >= 0) && (tempArray[k] != i) && (tempArray[k] != v))
			{
				cout << " -> " << tempArray[k];
				k--;
			}
			
			if (dist[i] != 0)
				cout << " -> " << i << endl; //print out the last vertex in path
			else
				cout << endl;
		}
	}


}

