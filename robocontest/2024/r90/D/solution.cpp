#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;
    sort(begin(xs), end(xs));

    vector<int> ys(n);
    for (auto &y : ys) cin >> y;
    sort(rbegin(ys), rend(ys));

    ll result{};

    while (!empty(xs)) {
        const auto a = stoll(to_string(xs.back()) + to_string(ys.back()));
        result += a;
        xs.pop_back();
        ys.pop_back();
    }

    cout << result << '\n';
    return 0;
}
