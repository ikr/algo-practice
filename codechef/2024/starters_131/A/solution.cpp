#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const map<int, int> Opp{{1, 6}, {6, 1}, {2, 5}, {5, 2}, {3, 4}, {4, 3}};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N, K;
        cin >> N >> K;

        vector<int> A(N);
        for (auto &a : A) cin >> a;

        int cheated{};
        map<int, int> pq;
        for (const auto &a : A) {
            const auto d = Opp.at(a) - a;
            if (d > 0) ++pq[d];
        }

        while (K && !empty(pq)) {
            const auto [d, m] = *crbegin(pq);
            pq.erase(prev(cend(pq)));
            assert(m > 0);
            --K;
            cheated += d;
            if (m - 1 > 0) pq.emplace(d, m - 1);
        }

        cout << (cheated + accumulate(cbegin(A), cend(A), 0)) << '\n';
    }

    return 0;
}
