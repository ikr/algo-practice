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

int moves_to_sort(const vi &xs) {
    vi ds(sz(xs));
    adjacent_difference(cbegin(xs), cend(xs), begin(ds));

    const auto ltz = [](const int d) { return d < 0; };
    const auto negatives = inof(count_if(next(cbegin(ds)), cend(ds), ltz));
    if (negatives > 1) return -1;
    if (negatives == 0) return 0;

    const auto it = find_if(next(cbegin(ds)), cend(ds), ltz);
    assert(it != cend(ds));
    const int i = inof(distance(cbegin(ds), it));
    assert(i > 0);

    return xs[0] >= xs.back() ? 1 : -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        const auto ans = moves_to_sort(xs);
        if (ans >= 0) {
            cout << "YES\n" << ans << '\n';
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
