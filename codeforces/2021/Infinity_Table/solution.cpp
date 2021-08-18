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

static constexpr int K_MAX = 1'000'000'000;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto side = [](const ll i) { return i + 1LL; };
    const auto perimeter = [&](const ll i) -> ll {
        return 2LL * side(i) - 1LL;
    };

    vi xs{1};
    for (ll i = 1; llof(xs.back()) + perimeter(i) <= llof(K_MAX); ++i) {
        xs.push_back(xs.back() + inof(perimeter(i)));
    }
    xs.push_back(xs.back() + inof(perimeter(sz(xs))));

    const auto head = [&](const int i) -> int {
        return i ? (xs[i - 1] + 1) : 1;
    };

    const auto resolve_coord = [&](const int k) -> pii {
        const auto it = lower_bound(cbegin(xs), cend(xs), k);
        const auto i = distance(cbegin(xs), it);

        const int bottom_right_row = inof(side(i)) - 1;
        const int bottom_right_val = head(inof(i)) + bottom_right_row;

        if (head(inof(i)) <= k && k <= bottom_right_val) {
            return {k - head(inof(i)), i};
        }

        return {i, xs[i] - k};
    };

    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> k;

        const auto [ro, co] = resolve_coord(k);
        cout << (ro + 1) << ' ' << (co + 1) << '\n';
    }

    return 0;
}
