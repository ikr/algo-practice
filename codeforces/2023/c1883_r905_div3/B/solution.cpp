#include <bits/stdc++.h>
using namespace std;

static constexpr int Az = 26;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const string &xs, int k) {
    array<int, Az> freq{};
    for (const auto x : xs) ++freq[x - 'a'];

    int evs{};
    vector<int> ods;
    for (const auto f : freq) {
        if (f % 2) {
            ods.push_back(f);
        } else {
            evs += f;
        }
    }

    sort(rbegin(ods), rend(ods));

    for (auto &f : ods) {
        const auto d = min(k, 1);
        f -= d;
        k -= d;
    }

    vector<int> ods_;
    for (const auto f : ods) {
        if (f % 2) {
            ods_.push_back(f);
        } else {
            evs += f;
        }
    }

    if (k) {
        assert(empty(ods_));
        return true;
    }

    return sz(ods_) < 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << (is_possible(xs, k) ? "YES" : "NO") << '\n';
    }

    return 0;
}
