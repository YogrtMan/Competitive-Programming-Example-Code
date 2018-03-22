#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <map>
#include <cstdlib>
#include <fstream>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)
//#define FILE

const long long INF = (long long)1000000000*10000;

class UFDS {
	public:
		vector<int> root, rank;
		UFDS(int n) {
			root.resize(n);
			rank.resize(n);
			for (int i = 0; i < n; i++) {
				root[i] = i;
				rank[i] = 0;
			}
		}
		int find(int n) {
			if (root[n] == n)
				return n;

			return root[n] = find(root[n]);

		}

		void union_(int n, int m) {
			int rn = find(n), rm = find(m);
			if (rank[rn] > rank[rm]) {
				root[rm] = root[rn];
				rank[rn]++;
			}
			else if (rank[rn] < rank[rm]) {
				root[rn] = root[rm];
				rank[rm]++;
			}
			else
				root[rm] = root[rn];
		}
};

vector<int> nodeType, distTo;
vector<vector<pair<int, int> > > adjList;
vector<pair<int, pair<int, int> > > edgeList;

//shortest distance from >0 to 4
vector<long long> dp;


long long dijkstra(int node) {
	vector<long long> dist(adjList.size(), INF);
	priority_queue<pair<long long, int> > q;
	dist[node] = 0;
	q.push(make_pair(0, node));

	while(!q.empty()) {
		int cur = q.top().second;
		long long curDist = -q.top().first;
		curDist -= dp[cur];
		q.pop();

		if (nodeType[cur] == nodeType[node]+1)
			return dist[cur]+dp[cur];

		FOR(i, adjList[cur].size()) {
			if (curDist + adjList[cur][i].second < dist[adjList[cur][i].first]) {
				dist[adjList[cur][i].first] = curDist + adjList[cur][i].second;

				q.push(make_pair(-(dist[adjList[cur][i].first]+dp[adjList[cur][i].first]), adjList[cur][i].first));
			}
		}
	}

	return INF;
}

int main() {
	int N, M;
	#ifdef FILE
		ifstream fin("pawpsicles.txt");
		fin >> N >> M;
	#else
		cin >> N >> M;
	#endif

	//throwaway first node for convenience
	nodeType.resize(N+1), adjList.resize(N+1);

	vector<vector<int> > typeN(5);
	FOR(i, N) {
		#ifdef FILE
			fin >> nodeType[i+1];
		#else
			cin >> nodeType[i+1];
		#endif
		typeN[nodeType[i+1]].push_back(i+1);
	}
	nodeType[0] = 0;

	FOR(i, M) {
		int from, to, cost;
		#ifdef FILE
			fin >> from >> to >> cost;
		#else
			cin >> from >> to >> cost;
		#endif
		edgeList.push_back(make_pair(cost, make_pair(from, to)));
	}

	UFDS uset(N+1);
	sort(edgeList.begin(), edgeList.end());
	int k = 0, edges=0;
	while(k < edgeList.size() && edges<N-1) {
		if (uset.find(edgeList[k].second.first) != uset.find(edgeList[k].second.second)) {
			adjList[edgeList[k].second.first].push_back(make_pair(edgeList[k].second.second, edgeList[k].first));
			adjList[edgeList[k].second.second].push_back(make_pair(edgeList[k].second.first, edgeList[k].first));
			edges++;
		}
		k++;
	}
	adjList[0].push_back(make_pair(1, 0));
	dp.assign(N+1, 0);

	//minimize distance from all type3 to type4
	FOR(i, typeN[3].size()) {
		dp[typeN[3][i]] = dijkstra(typeN[3][i]);
	}
	//minimize distance from all type2 to type3
	FOR(i, typeN[2].size()) {
		dp[typeN[2][i]] = dijkstra(typeN[2][i]);
	}
	//minimize distance from all type1 to type2
	FOR(i, typeN[1].size()) {
		dp[typeN[1][i]] = dijkstra(typeN[1][i]);
	}

	long long out = dijkstra(0);
	if (out >= INF)
		cout << -1;
	else
		cout << out;
}
