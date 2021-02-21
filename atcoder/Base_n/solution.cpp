#include <bits/stdc++.h>
using namespace std;

optional<long long> interpret(const string &x, const long long base,
                              long long limit) {
    long long ans = 0;
    long long mul = 1LL;
    for (auto it = crbegin(x); it != crend(x); ++it) {
        const int d = (*it) - '0';
        if (mul > limit || d * mul > limit || ans + d * mul > limit) {
            return nullopt;
        }

        ans += d * mul;
        mul *= base;
    }

    return {ans};
}

int min_base(const string &x) {
    const int d = *max_element(cbegin(x), cend(x)) - '0';
    return d + 1;
}

long long bin_search_interpretations(const string &x, const long long m) {
    const long long b0 = min_base(x);
    const auto lo_v = interpret(x, b0, m);
    if (!lo_v || *lo_v > m) return 0;

    long long best = b0;
    long long lo = b0;
    long long hi = 1'000'000'000'000'000'000LL + 1LL;
    const auto hi_v = interpret(x, hi, m);
    assert(!hi_v || *hi_v > m);

    while (lo <= hi) {
        const auto mid = lo + (hi - lo) / 2LL;
        const auto mid_v = interpret(x, mid, m);

        if (!mid_v || *mid_v > m) {
            hi = mid - 1;
        } else {
            assert(*mid_v <= m);
            best = mid;
            lo = mid + 1;
        }
    }

    return best - b0 + 1;
}

long long suitable_interpretations_count(const string &x, const long long m) {
    if (x.size() == 1U) {
        const long long d = x[0] - '0';
        return d <= m ? 1 : 0;
    }

    return bin_search_interpretations(x, m);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string x;
    long long m;
    cin >> x >> m;

    cout << suitable_interpretations_count(x, m) << '\n';
    return 0;
}
