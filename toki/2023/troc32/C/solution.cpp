#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint998244353;

mint num_stimulated(const int N, const int M) {
    if (N == 3) {
        if (M < 3) return 0;
        return mint{M} * mint{M - 1} * mint{M - 2};
    }

    vector<mint> D(N, 0);
    D[0] = mint{M};
    D[1] = D[0] * mint{M - 1};
    D[2] = D[1] * mint{M - 1};

    for (int i = 3; i < N - 1; ++i) {
        D[i] = D[i - 1] * (i % 2 == 0 ? mint{M - 1} : mint{M - 2});
    }

    D[N - 1] = D[N - 2] * mint{M - 1};

    return D.back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    cout << num_stimulated(N, M).val() << '\n';
    return 0;
}
