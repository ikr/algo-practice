#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> size_t combine_hashes(const T &xs) {
    size_t seed = xs.size();
    for (const auto i : xs) seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}

size_t key(const int X, const vector<int> &wallet) {
    return 31 * hash<int>{}(X) + combine_hashes(wallet);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X;
    cin >> N >> X;

    vector<int> denomi(N);
    vector<int> wallet(N);
    for (int i = 0; i < N; ++i) cin >> denomi[i] >> wallet[i];

    unordered_map<size_t, bool> memo;
    const auto recur = [&](const auto self, const int x,
                           vector<int> &w) -> bool {
        const auto k = key(x, w);
        {
            const auto it = memo.find(k);
            if (it != cend(memo)) return it->second;
        }

        return memo[k] = [&]() -> bool {
            if (x == 0) return true;
            if (x < 0) return false;

            {
                int budget{};
                for (int i = 0; i < sz(w); ++i) {
                    budget += w[i] * denomi[i];
                }
                if (budget < x) return false;
            }

            for (int i = 0; i < sz(w); ++i) {
                if (!w[i]) continue;
                --w[i];
                if (self(self, x - denomi[i], w)) {
                    ++w[i];
                    return true;
                } else {
                    ++w[i];
                }
            }

            return false;
        }();
    };

    const auto yes = recur(recur, X, wallet);
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
