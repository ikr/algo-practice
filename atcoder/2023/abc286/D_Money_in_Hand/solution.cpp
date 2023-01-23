#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X;
    cin >> N >> X;

    int hi = X;
    vector<int> wallet(N);
    for (int i = 0; i < N; ++i) {
        int A, B;
        cin >> A >> B;

        for (int j = 1; j <= B; ++j) wallet.push_back(A);
        hi = max(hi, A);
    }

    // D[i][j] is true iﬀ it is possible to obtain exactly j yen with coins in
    // the wallet up to index i
    vector<vector<bool>> D(sz(wallet), vector(hi + 1, false));

    D[0][0] = true;
    D[0][wallet[0]] = true;

    for (int i = 1; i < sz(wallet); ++i) {
        for (int j = 0; j < sz(D[i]); ++j) {
            D[i][j] = D[i - 1][j];

            if (j - wallet[i] >= 0) {
                D[i][j] = D[i][j] || D[i - 1][j - wallet[i]];
            }
        }
    }

    const auto yes =
        any_of(cbegin(D), cend(D), [X](const auto &row) { return row[X]; });
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
