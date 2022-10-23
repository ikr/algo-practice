#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using tri = tuple<int, int, int>;

pair<int, int> solution(const vector<tri> &src, const int U) {
    const auto N = sz(src);
    vector<vector<int>> D(N, vector(U + 1, -1));

    {
        const auto [a, b, x] = src[0];
        if (U >= a) {
            D[0][U - a + b] = x;
        }
    }

    for (int i = 1; i < N; ++i) {
        const auto [a, b, x] = src[i];

        if (U >= a) {
            D[i][U - a + b] = x;
        }

        for (int u = 0; u <= U; ++u) {
            if (D[i - 1][u] >= 0 && (u - a + b) >= 0) {
                D[i][u - a + b] = max(D[i][u - a + b], D[i - 1][u] + x);
            }
        }
    }

    int reward{};
    int energy = U;

    for (int j = 0; j < sz(D.back()); ++j) {
        if (D.back()[j] >= reward) {
            reward = D.back()[j];
            energy = j;
        }
    }

    return {reward, energy};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, U;
    cin >> N >> U;

    vector<tri> src(N);
    for (auto &[a, b, x] : src) cin >> a >> b >> x;
    sort(begin(src), end(src));

    const auto [reward, energy] = solution(src, U);
    cout << reward << ' ' << energy << '\n';
    return 0;
}
