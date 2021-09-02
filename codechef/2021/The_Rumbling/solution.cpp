#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename Iter, typename R, typename Binop, typename Unaop>
R ttransform_reduce(Iter first, Iter last, R init, Binop binop, Unaop unaop) {
    return inner_product(first, last, first, init, binop,
                         [&unaop](const auto &x,
                                  __attribute__((unused))
                                  const auto &x_) { return unaop(x); });
}

ll energy_west(const char x, const pii cost) {
    const auto [cw, ccw] = cost;

    switch (x) {
    case 'N':
        return min(3LL * cw, 1LL * ccw);

    case 'E':
        return min(2LL * cw, 2LL * ccw);

    case 'S':
        return min(1LL * cw, 3LL * ccw);

    case 'W':
        return 0;

    default:
        assert(false && "energy_west");
        return -1;
    }
}

ll energy_east(const char x, const pii cost) {
    const auto [cw, ccw] = cost;

    switch (x) {
    case 'N':
        return min(1LL * cw, 3LL * ccw);

    case 'E':
        return 0;

    case 'S':
        return min(3LL * cw, 1LL * ccw);

    case 'W':
        return min(2LL * cw, 2LL * ccw);

    default:
        assert(false && "energy_west");
        return -1;
    }
}

ll min_energy(const string &xs, const pii cost) {
    ll curr = ttransform_reduce(
        cbegin(xs), cend(xs), 0LL, plus<ll>{},
        [cost](const char x) { return energy_west(x, cost); });

    ll ans = curr;

    for (int i = 0; i < sz(xs); ++i) {
        curr -= energy_west(xs[i], cost);
        curr += energy_east(xs[i], cost);
        ans = min(ans, curr);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        string xs(N, ' ');
        cin >> xs;

        int X, Y;
        cin >> X >> Y;

        cout << min_energy(xs, {X, Y}) << '\n';
    }

    return 0;
}
