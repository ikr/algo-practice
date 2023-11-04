#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint0 = atcoder::modint998244353;
using mint1 = atcoder::modint1000000007;
using ull = unsigned long long;
static constexpr ull M0 = 998244353;
static constexpr ull M1 = 1e9 + 7;

optional<int> solution0(const ull b) {
    for (int a = 1; a <= 100; ++a) {
        if (mint0{a}.pow(a) == mint0{b % M0}) return a;
    }
    return nullopt;
}

optional<int> solution1(const ull b) {
    for (int a = 1; a <= 100; ++a) {
        if (mint1{a}.pow(a) == mint1{b % M1}) return a;
    }
    return nullopt;
}

optional<int> solution(const ull b) {
    const auto a0 = solution0(b);
    const auto a1 = solution1(b);

    if (a0 && a1 && *a0 == *a1) {
        return *a0;
    }

    return nullopt;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ull b;
    cin >> b;
    const auto ans = solution(b);

    if (ans) {
        cout << *ans << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}
