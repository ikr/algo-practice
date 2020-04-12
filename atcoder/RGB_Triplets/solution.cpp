#include <bits/stdc++.h>
    
using namespace std;
    
int main() {    
    int n;
    string s;
    cin >> n >> s;
    
    int ans = 0;
    
    if (n >= 3) {
        for (int i = 0; i < n - 2; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                if (s[i] == s[j]) continue;
                
                for (int k = j + 1; k < n; ++k) {
                    if (s[i] != s[k] && s[j] != s[k] && j - i != k - j) ++ans;
                }
            }    
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
