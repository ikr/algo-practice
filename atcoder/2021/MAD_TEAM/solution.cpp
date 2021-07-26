#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Quint = array<int, 5>;
using vi = vector<int>;

bool team_exists_not_weaker_than(const vector<Quint> &xss, const int lo) {
    set<int> indicator_masks;

    for (const auto &xs : xss) {
        int mask = 0;

        for (int i = 0; i < sz(xs); ++i) {
            if (xs[i] >= lo) mask |= (1 << i);
        }

        indicator_masks.insert(mask);
    }

    vi ms(cbegin(indicator_masks), cend(indicator_masks));
    const int all_five = 0b11111;

    for (int i = 0; i < sz(ms); ++i) {
        for (int j = 0; j < sz(ms); ++j) {
            for (int k = 0; k < sz(ms); ++k) {
                if ((ms[i] | ms[j] | ms[k]) == all_five) return true;
            }
        }
    }

    return false;
}

int top_team_strength(const vector<Quint> &xss, const vi &vals) {
    int lo = vals[0];
    int hi = vals.back() + 1;

    assert(team_exists_not_weaker_than(xss, lo));
    assert(!team_exists_not_weaker_than(xss, hi));

    while (hi - lo > 1) {
        const int mi = lo + (hi - lo) / 2;

        if (team_exists_not_weaker_than(xss, mi)) {
            lo = mi;
        } else {
            hi = mi;
        }
    }

    return lo;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<Quint> xss(n);
    set<int> vals;

    for (auto &xs : xss) {
        for (auto &x : xs) {
            cin >> x;
            vals.insert(x);
        }
    }

    cout << top_team_strength(xss, vi(cbegin(vals), cend(vals))) << '\n';

    return 0;
}
