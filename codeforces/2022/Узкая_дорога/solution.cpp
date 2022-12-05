#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> solution(const vector<int> &xs) {
    vector<int> result(sz(xs), xs[0] - 1);

    for (int i = 1; i < sz(xs); ++i) {
        const auto speed = i + 1;
        result[i] = max(result[i - 1] + 1, xs[i] - speed);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    for (const auto x : solution(xs)) {
        cout << x << '\n';
    }
    return 0;
}
