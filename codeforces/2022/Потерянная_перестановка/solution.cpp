#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &xs, int s) {
    const auto [plo, phi] = minmax_element(cbegin(xs), cend(xs));
    set<int> xss(cbegin(xs), cend(xs));

    {
        auto lo = *plo;
        while (s && lo > 1) {
            if (s - (lo - 1) < 0) return false;
            --lo;
            s -= lo;
            xss.insert(lo);
        }
    }

    for (int x = *plo; x <= *phi; ++x) {
        if (!xss.count(x)) {
            if (s < x) return false;
            s -= x;
            xss.insert(x);
        }
    }

    for (int x = *phi + 1; !!s; ++x) {
        if (s < x) return false;
        s -= x;
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, s;
        cin >> n >> s;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << (is_possible(xs, s) ? "YES" : "NO") << '\n';
    }

    return 0;
}
