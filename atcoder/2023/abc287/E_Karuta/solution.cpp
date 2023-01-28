#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

static constexpr ull MM = 20170123456789ULL;
static constexpr int AZ = 26;

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
        ull m = 1;
        ull h{};

        for (const auto x : xs) {
            ull a = inof(x) - inof('a');
            a *= m;
            a %= MM;

            h += a;
            h %= MM;

            ++hash_freqs[h];

            m *= AZ;
            m %= MM;
        }
    }

    vector<int> ans(N, 0);
    for (int i = 0; i < N; ++i) {
        const auto &xs = xss[i];
        ull m = 1;
        ull h{};

        for (int l = 1; l <= sz(xs); ++l) {
            const auto x = xs[l - 1];
            ull a = inof(x) - inof('a');
            a *= m;
            a %= MM;

            h += a;
            h %= MM;

            if (hash_freqs[h] > 1) {
                ans[i] = l;
            } else {
                break;
            }

            m *= AZ;
            m %= MM;
        }
    }

    for (const auto a : ans) {
        cout << a << '\n';
    }
    return 0;
}
