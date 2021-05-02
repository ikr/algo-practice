#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Quint = array<int, 5>;

int maximin(const Quint &q1, const Quint &q2) {
    Quint his;
    for (int i = 0; i < sz(his); ++i) his[i] = max(q1[i], q2[i]);
    return *min_element(cbegin(his), cend(his));
}

int maximin(const Quint &q1, const Quint &q2, const Quint &q3) {
    Quint his;
    for (int i = 0; i < sz(his); ++i) his[i] = max({q1[i], q2[i], q3[i]});
    return *min_element(cbegin(his), cend(his));
}

int top_team_strength(const vector<Quint> &xss) {
    int i0 = 0;
    int j0 = 1;
    int best = maximin(xss[i0], xss[j0]);

    for (int i = 0; i < sz(xss) - 1; ++i) {
        for (int j = i + 1; j < sz(xss); ++j) {
            if (i == 0 && j == 1) continue;
            const int challenger = maximin(xss[i], xss[j]);

            if (challenger > best) {
                i0 = i;
                j0 = j;
                best = challenger;
            }
        }
    }

    best = maximin(xss[0], xss[1], xss[2]);

    for (int i = 0; i < sz(xss); ++i) {
        if (i == i0 || i == j0) continue;
        best = max(best, maximin(xss[i0], xss[j0], xss[i]));
    }

    return best;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<Quint> xss(n);
    for (auto &xs : xss) {
        for (auto &x : xs) cin >> x;
    }

    cout << top_team_strength(xss) << '\n';

    return 0;
}
