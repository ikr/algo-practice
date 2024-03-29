#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int button_presses_num(const string &bits, const vector<int> &bs) {
    vector<int> xs(sz(bits));
    ranges::transform(bits, xs.begin(), [](const char c) { return c - '0'; });

    {
        vector<int> fs(sz(bits), 0);
        for (const auto b : bs) ++fs[b];

        for (int i = 1; i < sz(xs); ++i) {
            for (int p = 1; 1LL * p * p <= 1LL * i; ++p) {
                if (i % p) continue;
                const auto q = i / p;

                xs[i] += fs[p];
                if (p != q) xs[i] += fs[q];
                xs[i] %= 2;
            }
        }
    }

    // cerr << "xs: " << xs << endl;

    int ans{};

    {
        // All previous that we flipped
        vector<int> fs(sz(xs), 0);

        for (int i = 1; i < sz(xs); ++i) {
            for (int p = 1; 1LL * p * p <= 1LL * i; ++p) {
                if (i == p || i % p) continue;
                const auto q = i / p;

                xs[i] += fs[p];
                if (p != q) xs[i] += fs[q];
                xs[i] %= 2;
            }

            ans += xs[i];
            if (xs[i]) ++fs[i];
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        string xs;
        cin >> xs;
        assert(sz(xs) == N);
        xs = "0" + xs;

        int Q;
        cin >> Q;
        vector<int> bs(Q);
        for (auto &b : bs) cin >> b;

        cout << "Case #" << i << ": " << button_presses_num(xs, bs) << '\n';
    }

    return 0;
}
