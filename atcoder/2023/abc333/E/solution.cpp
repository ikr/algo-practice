#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

static constexpr int HI = 200'000;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<pii> events(N);
    for (auto &[t, x] : events) cin >> t >> x;

    vector<int> picks;
    vector<int> need(HI + 1, 0);

    for (const auto &[t, x] : events | ranges::views::reverse) {
        if (t == 1) {
            if (need[x] > 0) {
                picks.push_back(1);
                --need[x];
            } else {
                picks.push_back(0);
            }
        } else {
            assert(t == 2);
            ++need[x];
        }
    }

    if (any_of(cbegin(need), cend(need), [](const int x) { return x > 0; })) {
        cout << -1 << '\n';
        return 0;
    }

    ranges::reverse(picks);
    int i{};
    int potions{};
    int K{};
    for (const auto &[t, x] : events) {
        if (t == 1) {
            if (picks[i] == 1) {
                ++potions;
                K = max(K, potions);
            }
            ++i;
        } else {
            assert(t == 2);
            --potions;
        }
    }

    cout << K << '\n';
    cout << picks << '\n';
    return 0;
}
