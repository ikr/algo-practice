#include <algorithm>
#include <bits/stdc++.h>
#include <iterator>
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

using Tri = tuple<int, int, int>;

ostream &operator<<(ostream &os, const Tri &x) {
    const auto [i, j, k] = x;
    os << '(' << i << ' ' << j << ' ' << k << ')';
    return os;
}

int query(const Tri ijk, int &Q) {
    assert(Q > 0);

    const auto [i, j, k] = ijk;
    assert(i != j && j != k && i != k);
    cout << i << ' ' << j << ' ' << k << endl;

    int ans;
    cin >> ans;
    --Q;

    return ans;
}

using Iter = vi::const_iterator;

vi one_to(const int N) {
    vi ans(N);
    iota(begin(ans), end(ans), 1);
    return ans;
}

pair<Iter, Iter> edges(const pii bounds, const pair<Iter, Iter> range, int &Q) {
    const auto [first, last] = range;
    assert(distance(first, last) > 1);
    pair<Iter, Iter> ans{first, next(first)};

    if (bounds.first) {
        if (query({bounds.first, *ans.first, *ans.second}, Q) != *ans.first) {
            swap(ans.first, ans.second);
        }
    } else if (bounds.second) {
        if (query({*ans.first, *ans.second, bounds.second}, Q) != *ans.second) {
            swap(ans.first, ans.second);
        }
    }

    for (auto it = first; it != last; ++it) {
        if (it == ans.first || it == ans.second) continue;

        const auto mid = query({*ans.first, *ans.second, *it}, Q);
        if (mid == *ans.first) {
            ans.first = it;
        } else if (mid == *ans.second) {
            ans.second = it;
        }
    }

    return ans;
}

vi concat(vi xs, const vi &ys, const vi &zs) {
    xs.insert(cend(xs), cbegin(ys), cend(ys));
    xs.insert(cend(xs), cbegin(zs), cend(zs));
    return xs;
}

vi med_sort(const pii bounds, const pair<Iter, Iter> range, int &Q) {
    const auto [first, last] = range;
    if (distance(first, last) < 2) return vi(first, last);

    const auto [it, jt] = edges(bounds, range, Q);
    assert(it != last);
    assert(jt != last);
    assert(distance(it, jt) > 0);

    const int a = *it;
    const int b = *jt;

    return concat(med_sort({bounds.first, a}, {first, it}, Q),
                  med_sort({a, b}, {next(it), jt}, Q),
                  med_sort({b, bounds.second}, {next(jt), last}, Q));
}

vi derive_order(const int N, int &Q) {
    vi xs = one_to(N);
    return med_sort({0, 0}, {cbegin(xs), cend(xs)}, Q);
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
