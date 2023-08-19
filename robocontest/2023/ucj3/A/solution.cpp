#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N, M, K;
        cin >> N >> M >> K;

        const auto full_cycles = min({N, M / 2, K});

        N -= full_cycles;
        M -= 2 * full_cycles;
        K -= full_cycles;

        int ans = 4 * full_cycles;

        if (N) {
            ++ans;
            --N;

            if (M) {
                ++ans;
                --M;
            }

            if (K) {
                ++ans;
                --K;
            }

            if (M) {
                ++ans;
                --M;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
