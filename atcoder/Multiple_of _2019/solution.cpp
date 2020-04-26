#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

bool is_cool(const string &s) {
    assert(s.size() <= 20);
    if (s.size() == 20 && s > "18446744073709551615") return false;
    return stoull(s) % 2019ULL == 0;
}

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);
    
    string s;
    cin >> s;
    
    int ans = 0;
    for (auto i = 0U; i < s.size(); ++i) {
        for (auto l = 4; l <= 20 && i + l - 1 < s.size(); ++l) {
            string x = s.substr(i, l);
            if (is_cool(x)) ++ans;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
