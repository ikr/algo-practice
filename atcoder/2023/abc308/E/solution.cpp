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

    vector<int> E0X0(sz(E[0]));
    for (int i = 0; i < sz(E[0]); ++i) {
        const auto it = lower_bound(cbegin(X[0]), cend(X[0]), E[0][i]);
        E0X0[i] = inof(cend(X[0]) - it);
    }

    vector<int> E0X1(sz(E[0]));
    for (int i = 0; i < sz(E[0]); ++i) {
        const auto it = lower_bound(cbegin(X[1]), cend(X[1]), E[0][i]);
        E0X1[i] = inof(cend(X[1]) - it);
    }

    vector<int> E0X2(sz(E[0]));
    for (int i = 0; i < sz(E[0]); ++i) {
        const auto it = lower_bound(cbegin(X[2]), cend(X[2]), E[0][i]);
        E0X2[i] = inof(cend(X[2]) - it);
    }

    vector<int> E1X0(sz(E[1]));
    for (int i = 0; i < sz(E[1]); ++i) {
        const auto it = lower_bound(cbegin(X[0]), cend(X[0]), E[1][i]);
        E1X0[i] = inof(cend(X[0]) - it);
    }

    vector<int> E1X1(sz(E[1]));
    for (int i = 0; i < sz(E[1]); ++i) {
        const auto it = lower_bound(cbegin(X[1]), cend(X[1]), E[1][i]);
        E1X1[i] = inof(cend(X[1]) - it);
    }

    vector<int> E1X2(sz(E[1]));
    for (int i = 0; i < sz(E[1]); ++i) {
        const auto it = lower_bound(cbegin(X[2]), cend(X[2]), E[1][i]);
        E1X2[i] = inof(cend(X[2]) - it);
    }

    vector<int> E2X0(sz(E[2]));
    for (int i = 0; i < sz(E[2]); ++i) {
        const auto it = lower_bound(cbegin(X[0]), cend(X[0]), E[2][i]);
        E2X0[i] = inof(cend(X[0]) - it);
    }

    vector<int> E2X1(sz(E[2]));
    for (int i = 0; i < sz(E[2]); ++i) {
        const auto it = lower_bound(cbegin(X[1]), cend(X[1]), E[2][i]);
        E2X1[i] = inof(cend(X[1]) - it);
    }

    vector<int> E2X2(sz(E[2]));
    for (int i = 0; i < sz(E[2]); ++i) {
        const auto it = lower_bound(cbegin(X[2]), cend(X[2]), E[2][i]);
        E2X2[i] = inof(cend(X[2]) - it);
    }

    ll ans{};

    for (const int im : M[0]) {
        {
            const auto it = lower_bound(cbegin(E[0]), cend(E[0]), im);
            if (it != cend(E[0])) {
                const auto i = inof(it - cbegin(E[0]));
                ans += E0X0[i];
                ans += 2 * E0X1[i];
                ans += E0X2[i];
            }
        }
        {
            const auto it = lower_bound(cbegin(E[1]), cend(E[1]), im);
            if (it != cend(E[1])) {
                const auto i = inof(it - cbegin(E[1]));
                ans += 2 * E1X0[i];
                ans += 2 * E1X1[i];
                ans += 3 * E1X2[i];
            }
        }
        {
            const auto it = lower_bound(cbegin(E[2]), cend(E[2]), im);
            if (it != cend(E[2])) {
                const auto i = inof(it - cbegin(E[2]));
                ans += E2X0[i];
                ans += 3 * E2X1[i];
                ans += E2X2[i];
            }
        }
    }

    for (const int im : M[1]) {
        {
            const auto it = lower_bound(cbegin(E[0]), cend(E[0]), im);
            if (it != cend(E[0])) {
                const auto i = inof(it - cbegin(E[0]));
                ans += 2 * E0X0[i];
                ans += 2 * E0X1[i];
                ans += 3 * E0X2[i];
            }
        }
        {
            const auto it = lower_bound(cbegin(E[1]), cend(E[1]), im);
            if (it != cend(E[1])) {
                const auto i = inof(it - cbegin(E[1]));
                ans += 2 * E1X0[i];
            }
        }
        {
            const auto it = lower_bound(cbegin(E[2]), cend(E[2]), im);
            if (it != cend(E[2])) {
                const auto i = inof(it - cbegin(E[2]));
                ans += 3 * E2X0[i];
            }
        }
    }

    for (const int im : M[2]) {
        {
            const auto it = lower_bound(cbegin(E[0]), cend(E[0]), im);
            if (it != cend(E[0])) {
                const auto i = inof(it - cbegin(E[0]));
                ans += E0X0[i];
                ans += 3 * E0X1[i];
                ans += E0X2[i];
            }
        }
        {
            const auto it = lower_bound(cbegin(E[1]), cend(E[1]), im);
            if (it != cend(E[1])) {
                const auto i = inof(it - cbegin(E[1]));
                ans += 3 * E1X0[i];
            }
        }
        {
            const auto it = lower_bound(cbegin(E[2]), cend(E[2]), im);
            if (it != cend(E[2])) {
                const auto i = inof(it - cbegin(E[2]));
                ans += E2X0[i];
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
