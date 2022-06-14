#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using pii = pair<int, int>;

ll d2(const pii a, const pii b) {
    const auto f = llof(a.first - b.first);
    const auto g = llof(a.second - b.second);
    return f * f + g * g;
}

int closest_index(const vector<pii> &XY, const vector<int> &A, const pii p) {
    return *min_element(cbegin(A), cend(A),
                        [&](const int i, const int j) -> bool {
                            return d2(p, XY[i]) < d2(p, XY[j]);
                        });
}

double min_R(const vector<pii> &XY, const vector<int> &A) {
    set<int> to_skip(cbegin(A), cend(A));
    vector<double> rs(sz(XY), 0.0);

    for (int i = 0; i < sz(XY); ++i) {
        if (to_skip.count(i)) continue;
        const auto j = closest_index(XY, A, XY[i]);
        rs[i] = max(rs[i], sqrt(doof(d2(XY[i], XY[j]))));
    }

    return *max_element(cbegin(rs), cend(rs));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(7) << fixed;

    int N, K;
    cin >> N >> K;

    vector<int> A(K);
    for (auto &a : A) {
        cin >> a;
        --a;
    }

    vector<pii> XY(N);
    for (auto &[x, y] : XY) cin >> x >> y;

    cout << min_R(XY, A) << '\n';
    return 0;
}
