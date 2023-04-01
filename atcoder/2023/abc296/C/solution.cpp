#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool has_diff_X(const vector<int> &xs, const int X) {
    if (!X) return true;

    set<int> xss;
    for (const auto a : xs) {
        if (xss.count(a - X) || xss.count(a + X)) return true;
        xss.insert(a);
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X;
    cin >> N >> X;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << (has_diff_X(xs, X) ? "Yes" : "No") << '\n';
    return 0;
}
