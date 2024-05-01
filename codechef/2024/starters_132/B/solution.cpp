#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<string> &ss) {
    const auto k = sz(ss[0]);
    unordered_set<string> idx(cbegin(ss), cend(ss));

    string needle(k, '0');
    for (int i = 0; i < k; ++i) {
        needle[i] = '1';
        if (!idx.contains(needle)) return false;
        needle[i] = '0';
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<string> ss(n);
        for (auto &s : ss) {
            cin >> s;
            assert(sz(s) == k);
        }

        cout << (is_possible(ss) ? "YES" : "NO") << '\n';
    }

    return 0;
}
