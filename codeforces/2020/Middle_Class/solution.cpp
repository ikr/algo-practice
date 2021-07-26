#include <bits/stdc++.h>
    
using namespace std;
    
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin >> T;
    for (int i = 0; i != T; ++i) {
        int n, x;
        cin >> n >> x;
    
        long long rich_sum = 0;
        int rich_count = 0;
        vector<int> poor;
        for (int i = 0; i != n; ++i) {
            int b;
            cin >> b;
    
            if (b < x) poor.push_back(b);
            else {
                rich_sum += b;
                ++rich_count;
            }
        }
    
        sort(poor.begin(), poor.end());
    
        while (!poor.empty() && (rich_sum + poor.back()) / (rich_count + 1LL) >= static_cast<long long>(x)) {
            rich_sum += poor.back();
            ++rich_count;
            poor.pop_back();
        }
    
        cout << rich_count << endl;
    }
    
    return 0;
}
