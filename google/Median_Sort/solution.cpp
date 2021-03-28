#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

int query(const tuple<int, int, int> ijk, int &Q) {
    assert(Q > 0);

    const auto [i, j, k] = ijk;
    assert(i != j && j != k && i != k);
    cout << i << ' ' << j << ' ' << k << endl;

    int ans;
    cin >> ans;
    --Q;

    return ans;
}

vi one_to(const int N) {
    vi ans(N);
    iota(begin(ans), end(ans), 1);
    return ans;
}

tuple<pii, vi, vi, vi> partition_around_first_two(const pii bounds,
                                                  const vi &xs, int &Q) {
    assert(sz(xs) > 1);
    const auto [a, b] = [bounds, &xs, &Q]() -> pii {
        if (bounds.first) {
            if (query({bounds.first, xs[0], xs[1]}, Q) != xs[0]) {
                return {xs[1], xs[0]};
            }
        } else if (bounds.second) {
            if (query({xs[0], xs[1], bounds.second}, Q) != xs[1]) {
                return {xs[1], xs[0]};
            }
        }

        return {xs[0], xs[1]};
    }();

    vi prefix;
    vi infix;
    vi suffix;

    for (const int x : xs) {
        if (x == a || x == b) continue;

        const auto mid = query({a, b, x}, Q);
        if (mid == a) {
            prefix.push_back(x);
        } else if (mid == b) {
            suffix.push_back(x);
        } else {
            assert(mid == x);
            infix.push_back(x);
        }
    }

    return {{a, b}, prefix, infix, suffix};
}

vi concat(vi xs, const int a, const vi &ys, const int b, const vi &zs) {
    xs.push_back(a);
    xs.insert(cend(xs), cbegin(ys), cend(ys));
    xs.push_back(b);
    xs.insert(cend(xs), cbegin(zs), cend(zs));
    return xs;
}

vi median_sort(const pii bounds, const vi &xs, int &Q) {
    if (sz(xs) < 2) return xs;

    const auto [ab, prefix, infix, suffix] =
        partition_around_first_two(bounds, xs, Q);

    return concat(median_sort({bounds.first, ab.first}, prefix, Q), ab.first,
                  median_sort({ab.first, ab.second}, infix, Q), ab.second,
                  median_sort({ab.second, bounds.second}, suffix, Q));
}

vi derive_order(const int N, int &Q) {
    return median_sort({0, 0}, one_to(N), Q);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int T, N, Q;
    cin >> T >> N >> Q;

    while (T--) {
        cout << derive_order(N, Q) << endl;
        int verdict;
        cin >> verdict;
    }

    return 0;
}
