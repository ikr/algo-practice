#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}
optional<int> isqrt(const int x) {
    const auto q = sqrt(doof(x));
    if (inof(q) * inof(q) == x) return inof(q);
    if (inof(q + 1) * inof(q + 1) == x) return inof(q + 1);
    if (inof(abs(q - 1)) * inof(abs(q - 1)) == x) return inof(abs(q - 1));
    return nullopt;
}

bool is_sq(const string &xs) {
    const auto n = sz(xs);
    const auto m = isqrt(n);
    if (!m) return false;

    const auto h = *m;
    const auto w = *m;

    const auto at = [&](const int r, const int c) -> bool {
        const auto i = r * w + c;
        assert(i < n);
        return xs[i] == '1';
    };

    for (int c = 0; c < w; ++c) {
        if (!at(0, c)) return false;
        if (!at(h - 1, c)) return false;
    }

    for (int r = 0; r < h; ++r) {
        if (!at(r, 0)) return false;
        if (!at(r, w - 1)) return false;
    }

    for (int r = 1; r < h - 1; ++r) {
        for (int c = 1; c < w - 1; ++c) {
            if (at(r, c)) return false;
        }
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << (is_sq(xs) ? "Yes" : "No") << '\n';
    }

    return 0;
}
