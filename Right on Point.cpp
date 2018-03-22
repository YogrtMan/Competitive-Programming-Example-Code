#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)

class FT
{
	public:
    vector<int> tree;
    FT(const vector<int>& Arg)
    {
        tree.resize(Arg.size());
 
        for(int i = 0 ; i<tree.size(); i++)
            increase(i, Arg[i]);
 
    }
    void increase(int i, int delta)
    {
        for (; i < (int)tree.size(); i |= i + 1)
            tree[i] += delta;
    }
    int getsum(int left, int right)
    {
        return sum(right) - sum(left-1); 
    }
    int sum(int ind)
    {
        int sum = 0;
        while (ind>=0)
        {
            sum += tree[ind];
            ind &= ind + 1;
            ind--;
        }
        return sum;
    }
};

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> pianos(n);
	FOR(i, n)
		cin >> pianos[i];
		
	FT fenwickTree(pianos);
	
	FOR(i, m) {
		int j, k, l, r;
		cin >> j >> k >> l >> r;
		j--;
		l--;
		r--;
		fenwickTree.increase(j, k-pianos[j]);
		pianos[j] = k;
		cout << fenwickTree.getsum(l, r) << endl;
	}
		
}
