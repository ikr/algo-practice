#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &xs) {
    vector<int> ev;
    vector<int> od;

    for (const auto x : xs) {
        if (x % 2) {
            od.push_back(x);
        } else {
            ev.push_back(x);
        }
    }

    sort(begin(ev), end(ev));
    sort(begin(od), end(od));

    if (ev.empty() || od.empty()) return true;

    if (ev[0] < od[0]) {
        return false;
    } else {
        assert(od[0] < ev[0]);
        return ev[0] > od[0];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << (is_possible(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
