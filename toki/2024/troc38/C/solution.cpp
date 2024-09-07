#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint998244353;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    set<int> A;
    for (int i = 0; i < m; ++i) {
        int a;
        cin >> a;
        --a;
        A.insert(a);
    }

    // D[i][j][k] is the answer up to index i, when we set the i-th hose to mode
    // j, and we need k hoses functioning on the right.
    vector<vector<vector<mint>>> D(n, vector(3, vector<mint>(2, mint{0})));

    if (A.contains(0) || A.contains(n - 1)) {
        cout << "0\n";
        return 0;
    }

    D[0][0][0] = mint{1};
    D[0][1][1] = mint{1};

    for (int i = 1; i < n; ++i) {
        if (A.contains(i)) {
            D[i][2][1] = D[i - 1][0][0] + D[i - 1][1][0];
        } else {

            D[i][0][0] = D[i - 1][0][0] + D[i - 1][1][0] + D[i - 1][1][1] +
                         D[i - 1][2][1];

            D[i][1][0] = D[i - 1][0][0] + D[i - 1][1][0];
            D[i][1][1] = D[i - 1][1][1] + D[i - 1][2][1];

            D[i][2][1] = D[i - 1][0][0] + D[i - 1][1][0];
        }
    }

    mint result{};
    for (const auto &dd : D.back()) result += dd[0];
    cout << result.val() << '\n';
    return 0;
}
