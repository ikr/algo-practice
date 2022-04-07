#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll desired_sum(const vector<int> &xs, const int m) {
    const auto hi = *max_element(cbegin(xs), cend(xs));
    const auto lacking = [&]() -> ll {
        ll result{};
        for (const auto x : xs) result += hi - x;
        return result;
    }();

    if (lacking > m) return -1;
    const auto r = llof(m) - lacking;
    const auto d = r / sz(xs);

    return (hi + d) * sz(xs);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    int m;
    cin >> m;

    cout << desired_sum(xs, m) << '\n';
    return 0;
}
