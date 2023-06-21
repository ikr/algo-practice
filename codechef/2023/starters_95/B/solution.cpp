#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

ll max_total_energy(const int H, const vector<int> &A, const vector<int> &B) {
    priority_queue<int> aa;
    for (const auto &x : A) aa.push(x);

    priority_queue<pii> bb;
    for (const auto &x : B) bb.emplace(x, H);

    ll result{};

    while (!aa.empty() && !bb.empty()) {
        const auto a = aa.top();
        aa.pop();

        const auto [b, h] = bb.top();
        assert(h > 0);
        bb.pop();

        const auto max_hours = div_ceil(a, b);
        const auto actual_hours = min(h, max_hours);

        const auto charged = min(a, actual_hours * b);
        result += charged;

        if (actual_hours < h) {
            bb.emplace(b, h - actual_hours);
        }

        if (charged < a) {
            aa.push(a - charged);
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N, M, H;
        cin >> N >> M >> H;

        vector<int> A(N);
        for (auto &a : A) cin >> a;

        vector<int> B(M);
        for (auto &b : B) cin >> b;

        cout << max_total_energy(H, A, B) << '\n';
    }

    return 0;
}
