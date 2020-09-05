#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> digits(ll n) {
    vector<int> ans;

    while (n) {
        ans.push_back(n % 10);
        n /= 10;
    }

    return ans;
}

ll recur(const ll n, const int s) {
    auto ds = digits(n);
    const int curr = accumulate(cbegin(ds), cend(ds), 0);
    if (curr <= s) return 0;

    const int d = n % 10;
    const int i = d ? (10 - d) : 0;

    const ll nn = (n + i) / 10LL;

    return i + 10LL * recur(nn, s);
}

ll min_moves(const ll n, const int s) { return recur(n, s); }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        int s;
        cin >> n >> s;
        cout << min_moves(n, s) << '\n';
    }

    return 0;
}
