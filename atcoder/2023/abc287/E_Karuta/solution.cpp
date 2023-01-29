#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

static constexpr ull MM = 9999999900000001ULL;
static constexpr int B = 27;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<string> xss(N);
    for (auto &xs : xss) cin >> xs;

    map<ull, int> hash_freqs;
    for (const auto &xs : xss) {
        ull h{};

        for (const auto x : xs) {
            h *= B;
            h += inof(x) - inof('`');
            h %= MM;

            ++hash_freqs[h];
        }
    }

    vector<int> ans(N, 0);
    for (int i = 0; i < N; ++i) {
        const auto &xs = xss[i];
        ull h{};

        for (int l = 1; l <= sz(xs); ++l) {
            const auto x = xs[l - 1];
            h *= B;
            h += inof(x) - inof('`');
            h %= MM;

            if (hash_freqs[h] > 1) {
                ans[i] = l;
            } else {
                break;
            }
        }
    }

    for (const auto a : ans) {
        cout << a << '\n';
    }
    return 0;
}
