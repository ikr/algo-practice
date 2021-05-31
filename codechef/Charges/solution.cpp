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

int initial_spread(const string &charges) {
    int ans = 0;

    for (int i = 1; i < sz(charges); ++i) {
        ans += (charges[i] == charges[i - 1] ? 2 : 1);
    }

    return ans;
}

void do_flip(string &charges, const int i) {
    charges[i] = charges[i] == '0' ? '1' : '0';
}

vi spread_at_every_step(string charges, const vi &flips) {
    if (sz(charges) == 1) return vi(sz(flips), 0);

    auto spread = initial_spread(charges);
    vi ans;
    ans.reserve(sz(flips));

    for (const auto i : flips) {
        if (i == 0) {
            if (charges[i] == charges[i + 1]) {
                --spread;
            } else {
                ++spread;
            }

            do_flip(charges, i);
            ans.push_back(spread);
            continue;
        }

        if (i == sz(charges) - 1) {
            if (charges[i - 1] == charges[i]) {
                --spread;
            } else {
                ++spread;
            }

            do_flip(charges, i);
            ans.push_back(spread);
            continue;
        }

        if (charges[i - 1] == charges[i]) {
            --spread;
        } else {
            ++spread;
        }

        if (charges[i] == charges[i + 1]) {
            --spread;
        } else {
            ++spread;
        }
        do_flip(charges, i);
        ans.push_back(spread);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        string charges(n, ' ');
        cin >> charges;

        vi flips(k);
        for (auto &f : flips) {
            cin >> f;
            --f;
        }

        const auto ans = spread_at_every_step(charges, flips);
        for (const auto dist : ans) cout << dist << '\n';
    }

    return 0;
}
