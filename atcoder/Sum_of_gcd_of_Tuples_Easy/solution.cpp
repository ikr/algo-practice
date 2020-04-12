#include <bits/stdc++.h>
    
using namespace std;
    
int main() {    
    int n;
    cin >> n;
    
    int ans = 0;
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                ans += gcd(i, gcd(j, k));
            }
        }    
    }
    
    cout << ans << endl;
    
    return 0;
}
