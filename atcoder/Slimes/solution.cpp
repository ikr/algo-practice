#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Iter = vll::iterator;

ll min_combo(vll &xs) {
    function<ll(Iter, Iter)> recur;

    recur = [&](const Iter first, const Iter last) -> ll {
        assert(first < last);
        if (distance(first, last) == 1) return *first;
        if (distance(first, last) == 2) return *first + *next(first);

        ll ans = 1e18;

        for (auto pivot = next(first); pivot != prev(last); ++pivot) {
            const auto before = prev(pivot);
            const auto after = next(pivot);

            *before += *pivot;
            const auto o1 =
                *before + recur(first, pivot) + recur(next(pivot), last);
            *before -= *pivot;

            *after += *pivot;
            const auto o2 =
                *after + recur(first, pivot) + recur(next(pivot), last);
            *after -= *pivot;

            ans = min({ans, o1, o2});
        }

        return ans;
    };

    return recur(begin(xs), end(xs));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;
    vll xs(n);
    for (auto &x : xs) cin >> x;

    cout << min_combo(xs) << '\n';
    return 0;
}
