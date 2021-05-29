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

    map<pii, int> fs;
    for (const auto xy : xys) ++fs[xy];

    vector<pii> by_x = xys;
    sort(begin(by_x), end(by_x));

    vector<pii> by_y = xys;
    sort(begin(by_y), end(by_y), [](const pii lhs, const pii rhs) {
        return flip_pair(lhs) < flip_pair(rhs);
    });

    vector<pii> xx{by_x[0], by_x[1], n > 3 ? by_x[2] : by_x[1], by_x[n - 1]};
    vector<pii> yy{by_y[0], by_y[1], n > 3 ? by_y[2] : by_y[1], by_y[n - 1]};

    cerr << xx << endl;
    cerr << yy << endl;

    if (cheb(xx[0], xx[3]) > cheb(yy[0], yy[3])) {
        if (cheb(xx[0], xx[2]) > cheb(xx[1], xx[3])) { // dropped xx[3]
            if (fs[xx[3]] == 1) drop_one(yy, xx[3]);
            cerr << "one" << endl;
            cerr << xx << endl;
            cerr << yy << endl;
            return max(cheb(xx[0], xx[2]), cheb(yy[0], yy.back()));
        } else { // dropped xx[0]
            if (fs[xx[0]] == 1) drop_one(yy, xx[0]);
            cerr << "two" << endl;
            cerr << xx << endl;
            cerr << yy << endl;
            return max(cheb(xx[1], xx[3]), cheb(yy[0], yy.back()));
        }
    } else {
        if (cheb(yy[0], yy[2]) > cheb(yy[1], yy[3])) { // dropped yy[3]
            if (fs[yy[3]] == 1) drop_one(xx, yy[3]);
            cerr << "three" << endl;
            return max(cheb(yy[0], yy[2]), cheb(xx[0], xx.back()));
        } else { // dropped yy[0]
            if (fs[yy[0]] == 1) drop_one(xx, yy[0]);
            cerr << "four" << endl;
            return max(cheb(yy[1], yy[3]), cheb(xx[0], xx.back()));
        }
    }
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
