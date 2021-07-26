#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

template <typename T> constexpr pair<T, T> flip_pair(const pair<T, T> xy) {
    return {xy.second, xy.first};
}

void drop_one(vector<pii> &xys, const pii xy) {
    for (auto it = cbegin(xys); it != cend(xys);) {
        if (*it == xy) {
            it = xys.erase(it);
        } else {
            ++it;
        }
    }
}

int cheb(const pii ab, const pii cd) {
    const auto [a, b] = ab;
    const auto [c, d] = cd;
    return max(abs(a - c), abs(b - d));
}

int sub_diameter(const vector<pii> &xys) {
    const int n = sz(xys);

    vector<int> by_x(n);
    iota(begin(by_x), end(by_x), 0);
    sort(begin(by_x), end(by_x),
         [&xys](const int i, const int j) { return xys[i] < xys[j]; });

    vector<int> by_y(n);
    iota(begin(by_y), end(by_y), 0);
    sort(begin(by_y), end(by_y), [&xys](const int i, const int j) {
        return flip_pair(xys[i]) < flip_pair(xys[j]);
    });

    set<int> interesting;

    for (const auto i : vi{by_x[0], by_x[1], by_x[n - 2], by_x[n - 1], by_y[0],
                           by_y[1], by_y[n - 2], by_y[n - 1]}) {
        interesting.insert(i);
    }

    vector<int> zz(cbegin(interesting), cend(interesting));

    priority_queue<int> pq;
    for (int i = 0; i < sz(zz) - 1; ++i) {
        for (int j = i; j < sz(zz); ++j) {
            if (zz[i] == zz[j]) continue;
            pq.push(cheb(xys[zz[i]], xys[zz[j]]));
        }
    }

    pq.pop();
    return pq.top();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vector<pii> xys(n);
    for (auto &[x, y] : xys) cin >> x >> y;

    cout << sub_diameter(xys) << endl;
    return 0;
}
