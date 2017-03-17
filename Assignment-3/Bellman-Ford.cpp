#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
using namespace std;

#define INF 1000000000ULL
#define mp make_pair
#define pb push_back
#define F first
#define S second

// V -> Number of Vertices
// E -> Number of Edges
// Adj -> Adjacency List (Implemented using vector data structure)

const int N = 100005;
int V, E, a, b, w, src;
int dist[N];
vector<pair<pair<int, int>, int> > Edges;

void init() // Initialising distances
{
	for(int i = 1; i<=V; i++)
		dist[i] = INF;
	dist[src] = 0;
	return;
}

void BellmanFord(int src)
{	
	/*
	Bellman-Ford works for all graphs which do not contain negative cycle.
	So assuming that the graph does not contain any negative cycle
	*/
	dist[src] = 0;
	for(int i = 1; i<V; i++)
	{
		for(int j = 1; j<=E; j++)
		{
			a = Edges[j-1].F.F;
			b = Edges[j-1].F.S;
			w = Edges[j-1].S;
			if(dist[a]!=INF)
				dist[b] = min(dist[b], dist[a] + w);
		}
	}
	return;
}

int main()
{	
	cin >> V >> E;
	for(int i = 1; i<=E; i++)
	{
		cin >> a >> b >> w; // Edge from a to b with weight w;
		Edges.pb(mp(mp(a, b), w));
	}
	cin >> src;
	init();
	BellmanFord(src);
	for(int i = 1; i<=V; i++)
		cout << i << " " << dist[i] << "\n";

	return 0;
}