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

vector<vector<bool> > graph;
vector<int> order;
vector<bool> visited, removed;

bool BFS(int start) {
	visited.assign(graph.size(), false);
	queue<int> q;
	q.push(start);
	visited[start] = true;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		FOR(i, graph[cur].size()) {
			if (graph[cur][i] && !removed[i] && !visited[i]) {
				visited[i] = true;
				q.push(i);
			}
		}
	}
	FOR(i, graph.size()) {
		if (!visited[i] && !removed[i])
			return false;
	}
	return true;
}

bool done() {
	FOR(i, graph.size()) {
		if (!removed[i])
			return false;
	}
	return true;
}

bool canRemoveNow(int v) {
	removed[v] = true;
	order.push_back(v);
	if (v == graph.size() - 1 && done())
		return true;
	else if (!BFS(v)) {
		if (!done()) {
			order.pop_back();
			removed[v] = false;
			return false;
		}
		else
			return true;
	}
	
	bool nowhereToGo = true;
	FOR(i, graph.size()) {
		if (graph[v][i] && !removed[i]) {
			nowhereToGo = false;
			if (canRemoveNow(i)) {
				return true;
			}
		}
	}
	if (nowhereToGo && done())
		return true;
	else if (nowhereToGo) {
		removed[v] = false;
		order.pop_back();
		return false;
	}
	removed[v] = false;
	order.pop_back();
	return false;
}

int main() {
	int n, m;
	cin >> n >> m;
	graph.resize(n);
	removed.assign(n, false);
	
	FOR(i, n)
		graph[i].assign(n, false);
	
	FOR(i, m) {
		int from, to;
		cin >> from >> to;
		from--;
		to--;
		graph[from][to] = true;
		graph[to][from] = true;
	}
	
	FOR(i, n) {
		removed.assign(n, false);
		order.resize(0);
		if (canRemoveNow(i)) {			
			FOR(i, order.size())
				cout << order[i]+1 << " ";
			return 0;
		}	
	}
	cout << "It has to be this way" << endl;
	
}

