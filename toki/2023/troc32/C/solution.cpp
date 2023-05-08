#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint998244353;

mint num_stimulated(const int N, const int M) {
    if (N == 2) return mint{M}.pow(2);

    if (N == 3) {
        if (M < 3) return 0;
        return mint{M} * mint{M - 1} * mint{M - 2};
    }

    return mint{M} * mint{M - 2} * mint{M - 1}.pow(N - 2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    cout << num_stimulated(N, M).val() << '\n';
    return 0;
}
