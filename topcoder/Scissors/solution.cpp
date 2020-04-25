#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int log_2_floor(const ll n) {
    int ans = 0;
    ll e = 1;
    
    while (e * 2 <= n) {
    	++ans;
        e *= 2;
    }
    
    return ans;
}

struct Scissors final {
	int openingTime(const int n) const {
  		const int p = log_2_floor(n);
        const int e = 1 << p;
        
        return p * 10 + (e == n ? 0 : 10);
    }
};
