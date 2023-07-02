#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    string S;
    cin >> S;
    assert(sz(S) == N);

    array<vector<int>, 3> M{};
    array<vector<int>, 3> E{};
    array<vector<int>, 3> X{};

    for (int i = 0; i < N; ++i) {
        switch (S[i]) {
        case 'M':
            M[A[i]].push_back(i);
            break;
        case 'E':
            E[A[i]].push_back(i);
            break;
        case 'X':
            X[A[i]].push_back(i);
            break;
        }
    }

    array<array<vector<int>, 3>, 3> EX{};
    for (int e = 0; e < 3; ++e) {
        for (int x = 0; x < 3; ++x) {
            EX[e][x].resize(sz(E[e]));

            for (int i = 0; i < sz(E[e]); ++i) {
                const auto it = lower_bound(cbegin(X[x]), cend(X[x]), E[e][i]);
                EX[e][x][i] = inof(cend(X[x]) - it);
            }

            partial_sum(crbegin(EX[e][x]), crend(EX[e][x]), rbegin(EX[e][x]));
        }
    }

    ll ans{};

    for (const int im : M[0]) {
        {
            const auto it = lower_bound(cbegin(E[0]), cend(E[0]), im);
            if (it != cend(E[0])) {
                const auto i = inof(it - cbegin(E[0]));
                ans += EX[0][0][i];
                ans += 2 * EX[0][1][i];
                ans += EX[0][2][i];
            }
        }
        {
            const auto it = lower_bound(cbegin(E[1]), cend(E[1]), im);
            if (it != cend(E[1])) {
                const auto i = inof(it - cbegin(E[1]));
                ans += 2 * EX[1][0][i];
                ans += 2 * EX[1][1][i];
                ans += 3 * EX[1][2][i];
            }
        }
        {
            const auto it = lower_bound(cbegin(E[2]), cend(E[2]), im);
            if (it != cend(E[2])) {
                const auto i = inof(it - cbegin(E[2]));
                ans += EX[2][0][i];
                ans += 3 * EX[2][1][i];
                ans += EX[2][2][i];
            }
        }
    }

    for (const int im : M[1]) {
        {
            const auto it = lower_bound(cbegin(E[0]), cend(E[0]), im);
            if (it != cend(E[0])) {
                const auto i = inof(it - cbegin(E[0]));
                ans += 2 * EX[0][0][i];
                ans += 2 * EX[0][1][i];
                ans += 3 * EX[0][2][i];
            }
        }
        {
            const auto it = lower_bound(cbegin(E[1]), cend(E[1]), im);
            if (it != cend(E[1])) {
                const auto i = inof(it - cbegin(E[1]));
                ans += 2 * EX[1][0][i];
            }
        }
        {
            const auto it = lower_bound(cbegin(E[2]), cend(E[2]), im);
            if (it != cend(E[2])) {
                const auto i = inof(it - cbegin(E[2]));
                ans += 3 * EX[2][0][i];
            }
        }
    }

    for (const int im : M[2]) {
        {
            const auto it = lower_bound(cbegin(E[0]), cend(E[0]), im);
            if (it != cend(E[0])) {
                const auto i = inof(it - cbegin(E[0]));
                ans += EX[0][0][i];
                ans += 3 * EX[0][1][i];
                ans += EX[0][2][i];
            }
        }
        {
            const auto it = lower_bound(cbegin(E[1]), cend(E[1]), im);
            if (it != cend(E[1])) {
                const auto i = inof(it - cbegin(E[1]));
                ans += 3 * EX[1][0][i];
            }
        }
        {
            const auto it = lower_bound(cbegin(E[2]), cend(E[2]), im);
            if (it != cend(E[2])) {
                const auto i = inof(it - cbegin(E[2]));
                ans += EX[2][0][i];
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
