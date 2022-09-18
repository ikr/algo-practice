#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool intersect(const pii a, const pii b) {
    const auto [aL, aR] = a;
    const auto [bL, bR] = b;
    return !(bR <= aL || aR <= bL);
}

struct Meeting final {
    int tli;
    int L;
    int R;
};

int min_cancelled(const int N, const int K, const vector<Meeting> &ms,
                  const int D, const int X) {
    const auto meetings_num_by_tech_lead =
        [&](const pii suggested) -> vector<int> {
        vector<int> result(N, 0);
        for (const auto &[tli, L, R] : ms) {
            result[tli] += intersect({L, R}, suggested);
        }
        return result;
    };

    int result = sz(ms);

    for (int start = 0; start + X <= D; ++start) {
        const auto fq = meetings_num_by_tech_lead({start, start + X});

        for (int bits = 1; bits < (1 << N); ++bits) {
            if (__builtin_popcount(bits) != K) continue;
            int cur{};

            for (int j = 0; j < N; ++j) {
                if ((1 << j) & bits) cur += fq[j];
            }

            result = min(result, cur);
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, K, X, D;
        cin >> N >> K >> X >> D;

        int M;
        cin >> M;

        vector<Meeting> ms(M);
        for (auto &[tli, L, R] : ms) {
            cin >> tli >> L >> R;
            --tli;
        }

        cout << "Case #" << i << ": " << min_cancelled(N, K, ms, D, X) << '\n';
    }

    return 0;
}
