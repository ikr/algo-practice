#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

using mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int num_ways(const string &xs) {
    const map<char, int> idx{{'c', 0}, {'h', 1}, {'o', 2}, {'k', 3},
                             {'u', 4}, {'d', 5}, {'a', 6}, {'i', 7}};

    array<mint, 8> dp;

    for (const auto x : xs) {
        if (!idx.count(x)) continue;
        const int k = idx.at(x);

        if (k == 0) {
            dp[0] += 1;
            continue;
        }

        dp[k] += dp[k - 1];
    }

    return dp.back().val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    string xs;
    cin >> xs;

    cout << num_ways(xs) << '\n';

    return 0;
}
