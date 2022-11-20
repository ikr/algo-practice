#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

enum class Dir { W, E };

struct State final {
    int a;
    Dir da;

    int b;
    Dir db;

    ll t;
};

vector<State> initial_states(const vector<int> &xs) {
    if (sz(xs) == 1) {
        return {State{xs[0] - 1, Dir::W, xs[0] + 1, Dir::E, 1}};
    }

    const auto lo = xs[0];
    const auto hi = xs.back();

    vector<State> result{State{lo - 1, Dir::W, hi - 1, Dir::W, 1}};

}

ll dual_roundtrip_time(const int L, const vector<int> &xs) { return -1; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, L;
    cin >> N >> L;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << dual_roundtrip_time(L, xs) << '\n';
    return 0;
}
