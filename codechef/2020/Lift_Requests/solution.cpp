#include <bits/stdc++.h>

using namespace std;

using LL = long long;

int main() {
    int t;
    cin >> t;
    
    for (int tc = 0; tc < t; ++tc) {
        int n, q;
        cin >> n >> q;
        
        LL ans = 0;
        int y = 0;
        
        for (int i = 0; i < q; ++i) {
            int f, d;
            cin >> f >> d;
            
            ans += abs(y - f) + abs(d - f);
            y = d;
        }
        
        cout << ans << endl;
    }
    
    return 0;
}
