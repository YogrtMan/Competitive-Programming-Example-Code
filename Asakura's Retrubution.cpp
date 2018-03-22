#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)
#define INF 10000000;

int n, m;
vector<int> parent, toRemove1, toRemove2;
vector<vector<int> > graph, flow, flowUsed, paths;

vector<bool> visitedInFlow;
vector<pair<int, int> > arr;
vector<int> subset;

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

bool connectedToSink(int v) {
	if (v == (graph.size()/2)-1)
		return true;
	FOR(i, graph[v].size()) {
		if (connectedToSink(graph[v][i]))
			return true;
	}
	return false;
}

long long edmondsKarp(int source, int sink) {
	long long maxFlow = 0, tempFlow;
	while((tempFlow = BFS(source, sink)) != 0) {
		maxFlow += tempFlow;
		int cur = sink;
		while(cur != source) {

			if (parent[cur] >= n) {
				visitedInFlow[parent[cur]-n] = true;
			}
			else
				visitedInFlow[parent[cur]] = true;
			
			if (cur >= n) {
				visitedInFlow[cur-n] = true;
			}
			else
				visitedInFlow[cur] = true;
				
			flowUsed[parent[cur]][cur] += tempFlow;
			flowUsed[cur][parent[cur]] -= tempFlow;
			cur = parent[cur];
		}
	}
	return maxFlow;
}

bool subsetSum(int n, int sum, int tar) {
	if (sum == tar) {
		return true;
	}
	else if (n >= arr.size())
		return false;
	else if (n == arr.size()-1) {
		if (sum + arr[n].first != tar)
			return false;
		else {
			subset.push_back(arr[n].second);
			return true;
		}
	}
	
	if (subsetSum(n+1, sum+arr[n].first, tar)) {
		subset.push_back(arr[n].second);
		return true;
	}
	else if (subsetSum(n+1, sum, tar)) {
		return true;
	}
	else {
		return false;
	}
}

int main() {	
	cin >> n;
	graph.resize(n*2);
	flow.resize(n*2);
	flowUsed.resize(n*2);
	parent.resize(n*2);
	visitedInFlow.assign(n, false);
	
	FOR(i, n*2) {
		flow[i].assign(n*2, 0);
		flowUsed[i].assign(n*2, 0);
	}
	
	FOR(i, n) {
		int temp;
		cin >> temp;
		if (temp == -1)
			temp = INF;
		graph[i].push_back(n+i);
		graph[n+i].push_back(i);
		flow[i][n+i] = temp;
	}
	
	cin >> m;
	FOR(i, m) {
		int from, to;
		cin >> from >> to;
		from--;
		to--;
		graph[from+n].push_back(to);
		graph[to].push_back(from+n);
		flow[from+n][to] = INF;
	}

	int minCut = edmondsKarp(0, graph.size()-1);
	FOR(i, visitedInFlow.size()) {
		if (visitedInFlow[i]) {
			arr.push_back(make_pair(flow[i][i+n], i));
		}
	}
	subsetSum(0, 0, minCut);
	sort(subset.begin(), subset.end());
	
	cout << minCut << endl;
	cout << subset.size() << endl;
	FOR(i, subset.size()) {
		cout << subset[i]+1 << " ";
	}
}
