#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int cmp(pii a, pii b) {
    const auto common = lcm(a.second, b.second);
    const auto a_ = common / a.second;
    const auto b_ = common / b.second;

    a.first *= a_;
    b.first *= b_;
    if (a.first == b.first) return 0;
    return a.first < b.first ? -1 : 1;
}

pii find_pq(const int N) {
    pii ans{0, 1};
    for (int p = 1; p <= N / 2; ++p) {
        const auto q = N - p;
        if (gcd(p, q) != 1) continue;

        if (cmp(ans, {p, q}) < 0) {
            ans = {p, q};
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;
    const auto [p, q] = find_pq(N);
    cout << p << ' ' << q << '\n';
    return 0;
}
