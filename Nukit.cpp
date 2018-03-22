#include <iostream>
#include <vector>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)

vector<vector<vector<vector<vector<short> > > > > pWin;

bool solve(int a, int b, int c, int d, bool pTurn) {
	if (a < 0 || b < 0 || c < 0 || d < 0) {
//		cout << pTurn << " return " << !pTurn << endl;
		return 0;
	}
	
	if (pWin[pTurn][a][b][c][d] == -1) {
		pWin[pTurn][a][b][c][d] = (
			solve(a-2, b-1, c, d-2, !pTurn) ||
			solve(a-1, b-1, c-1, d-1, !pTurn) ||
			solve(a, b, c-2, d-1, !pTurn) ||
			solve(a, b-3, c, d, !pTurn) ||
			solve(a-1, b, c, d-1, !pTurn)
			);
	}
	cout << pTurn << " " << a << " " << b << " " << c << " " << d << ": " << pWin[pTurn][a][b][c][d] << endl;
	return pWin[pTurn][a][b][c][d];
}

int main() {
//	int a = 1;
//	cout << bool(!a);
	pWin.resize(2);
	FOR(p, pWin.size()) {
		pWin[p].resize(31);
		FOR(i, pWin[p].size()) {
			pWin[p][i].resize(31);
			FOR(j, pWin[p][i].size()) {
				pWin[p][i][j].resize(31);
				FOR(k, pWin[p][i][j].size()) {
					pWin[p][i][j][k].assign(31, -1);
				}
			}
		}
	}
	
	int t;
	cin >> t;
	while(t--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		cout << (solve(a, b, c, d, 1) ? "Patrick" : "Roland") << endl;
	}
}
