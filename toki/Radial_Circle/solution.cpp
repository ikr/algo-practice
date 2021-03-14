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

enum class Side { L, R };

constexpr Side disposition(const pii seg, const int x) {
    assert(seg.first < seg.second);
    assert(x != seg.first && x != seg.second);
    return (seg.first < x && x < seg.second) ? Side::R : Side::L;
}

int max_additional_segs(const int n, vector<pii> segs) {
    set<pii> s(cbegin(segs), cend(segs));

    int ans = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (s.count({i, j})) continue;

            bool intersects = false;

            for (const auto [a, b] : segs) {
                if (a == i || a == j || b == i || b == j) continue;

                if (disposition({i, j}, a) != disposition({i, j}, b)) {
                    intersects = true;
                    break;
                }
            }

            if (!intersects) {
                ++ans;
                s.emplace(i, j);
                segs.emplace_back(i, j);
            }
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n, m;
    cin >> n >> m;
    vector<pii> segs(m);
    for (auto &[a, b] : segs) {
        cin >> a >> b;
        --a;
        --b;

        if (b < a) swap(a, b);
    }

    cout << max_additional_segs(n, segs) << '\n';
    return 0;
}
