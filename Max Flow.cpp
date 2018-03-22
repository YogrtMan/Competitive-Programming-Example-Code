#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <queue>

using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)
#define INF 100000000;

vector<int> parent;
vector<vector<int> > graph, flow, flowUsed;

int BFS(int source, int sink) {
	vector<int> pathFlow(graph.size(), 0);
	parent.assign(parent.size(), -1);

	queue<int> q;
	q.push(source);
	pathFlow[source] = INF;
	parent[source] = -2;
	
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		FOR(i, graph[cur].size()) {
			if (parent[graph[cur][i]] == -1) {
				if (flow[cur][graph[cur][i]] - flowUsed[cur][graph[cur][i]] > 0) {
					pathFlow[graph[cur][i]] = min(pathFlow[cur], flow[cur][graph[cur][i]] - flowUsed[cur][graph[cur][i]]);
					parent[graph[cur][i]] = cur;
					if (graph[cur][i] == sink)
						return pathFlow[sink];
					q.push(graph[cur][i]);
				}
			}
		}
	}
	return 0;
}

int edmondsKarp(int source, int sink) {
	int maxFlow = 0, tempFlow;
	while((tempFlow = BFS(source, sink)) != 0) {
		maxFlow += tempFlow;
		int cur = sink;
		while(cur != source) {
			flowUsed[parent[cur]][cur] += tempFlow;
			flowUsed[cur][parent[cur]] -= tempFlow;
			cur = parent[cur];
		}
	}
	return maxFlow;
}
int main() {
	int n, m;
	cin >> n >> m;
	graph.resize(n);
	flow.resize(n);
	flowUsed.resize(n);
	parent.resize(n);
	FOR(i, n) {
		flow[i].assign(n, 0);
		flowUsed[i].assign(n, 0);
	}
	FOR(i, m) {
		int from, to, pathFlow;
		cin >> from >> to >> pathFlow;
		from--;
		to--;
		graph[from].push_back(to);
		graph[to].push_back(from);
		flow[from][to] = pathFlow;
	}
	cout << edmondsKarp(0, n-1);
}
