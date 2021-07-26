#include <bits/stdc++.h>
    
using namespace std;

using Int = long long;

int main() {    
    Int n;
    cin >> n;
    
    Int ans = 0;
    
    for (Int i = 1; i <= n; ++i) {
        if (i % 3 && i % 5) ans += i;
    }
    
    cout << ans << endl;
    
    return 0;
}
