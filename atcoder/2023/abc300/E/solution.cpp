#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using mint = atcoder::modint998244353;

mint probability_to_reach_N(const ll N) {
    unordered_map<ll, mint> memo;
    // Probability to reach N starting from k
    const auto recur = [&](const auto self, const ll k) -> mint {
        if (memo.count(k)) return memo.at(k);
        return memo[k] = [&]() -> mint {
            if (k == N) return 1;
            if (k > N) return 0;

            mint s{};
            for (ll i = 2; i <= 6; ++i) {
                s += self(self, i * k);
            }
            return s / 5;
        }();
    };

    return recur(recur, 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N;
    cin >> N;

    cout << probability_to_reach_N(N).val() << '\n';
    return 0;
}
