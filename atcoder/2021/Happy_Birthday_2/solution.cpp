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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

pair<vi, vi> idx_combos(const vi &xs) {
    vvi ss(200);

    for (int i = 0; i < sz(xs); ++i) {
        const int x = xs[i] % 200;
        if (!ss[x].empty()) return {ss[x], vi{i}};

        vector<pair<int, vi>> to_add;
        to_add.emplace_back(x, vi{i});

        for (int j = 0; j < sz(ss); ++j) {
            if (ss[j].empty()) continue;

            const int y = (j + x) % 200;
            if (!ss[y].empty()) {
                vi ys = ss[j];
                ys.push_back(i);
                return {ss[y], ys};
            }

            vi ys = ss[j];
            ys.push_back(i);
            to_add.emplace_back(y, ys);
        }

        for (const auto &[k, v] : to_add) {
            ss[k] = v;
        }
    }

    return {{}, {}};
}

void increment_all(vi &xs) {
    for (auto &x : xs) ++x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    auto [ys, zs] = idx_combos(xs);
    if (ys.empty()) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        increment_all(ys);
        increment_all(zs);

        cout << sz(ys) << ' ' << ys << '\n';
        cout << sz(zs) << ' ' << zs << '\n';
    }

    return 0;
}
