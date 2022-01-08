#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint998244353;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int LIM = 5000;

mint subseq_permutations_num(const string &xs) {
    vector<vector<mint>> memo(sz(xs), vector(sz(xs), mint{0}));

    function<mint(int, int)> calc;
    calc = [&](const int l, const int r) -> mint {
        if (memo[l][r] != mint{0}) return memo[l][r];

        return memo[l][r] = [&]() -> mint {
            if (l == r) return 1;
        }();
    };

    return calc(0, sz(xs));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    cout << subseq_permutations_num(xs).val() << '\n';
    return 0;
}
