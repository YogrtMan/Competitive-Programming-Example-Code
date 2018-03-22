#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)

int main() {
	int R, C, n;
	cin >> R >> C >> n;
	vector<vector<int> > diffArr(R);
	FOR(i, R)
		diffArr[i].assign(C, 0);
	
	FOR(k, n) {
		int r, c, guards, radius;
		cin >> c >> r >> radius >> guards;
		c--;
		r = R - r;
		for(int i = (r - radius); i <= (r + radius); i++) {
			if (i >= 0 && i < R) {
				int rangeHalf = sqrt((radius*radius)-((r-i)*(r-i)));
				if (c - rangeHalf >= 0)
					diffArr[i][c-rangeHalf] += guards;
				else
					diffArr[i][0] += guards;
					
				if (c + rangeHalf + 1 < C)
					diffArr[i][c+rangeHalf+1] -= guards;
				else
					diffArr[i][C] -= guards;
			}
		}
	}
	
	FOR(i, R) {
		for(int j = 1; j < C; j++) {
			diffArr[i][j] += diffArr[i][j-1];
		}
	}	
	int most = 0, counter = 0;
	FOR(i, R) {
		FOR(j, C) {
			if (diffArr[i][j] > most) {
				most = diffArr[i][j];
				counter = 1;
			}
			else if (diffArr[i][j] == most)
				counter++;
		}
	}
	cout << most << endl << counter << endl;
}
