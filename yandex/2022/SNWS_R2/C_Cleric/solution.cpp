#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr long double EPS = 0.000000001L;

int min_fights(const int n, const long double p, const map<int, int> &sfs) {
    vector<long double> outcomes(n + 1, 0.0);
    outcomes[0] = 1;

    for (auto [ans, tail] = pair{0, 0.0L};; ++ans) {
        const auto hi = outcomes[n] + tail;
        const auto lo =
            accumulate(cbegin(outcomes), cbegin(outcomes) + n, 0.0L);
        // cerr << outcomes << " lo:" << lo << " hi:" << hi << " tail:" << tail
        //      << endl;
        if (hi / (lo + hi) >= p) return ans;

        auto addition_to_tail = 0.0L;
        vector<long double> outcomes_(n + 1, 0.0L);

        for (int k = 0; k <= n; ++k) {
            if (outcomes[k] < EPS) continue;

            for (int i = 1; i <= 6; ++i) {
                if (k + i <= n) {
                    const auto j = sfs.count(k + i) ? sfs.at(k + i) : (k + i);
                    outcomes_[j] += outcomes[k];
                } else {
                    addition_to_tail += outcomes[k];
                }
            }
        }

        tail = tail * 6 + addition_to_tail;
        swap(outcomes, outcomes_);
    }

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    long double p;
    cin >> p;

    map<int, int> sfs;
    for (int i = 0; i < k; ++i) {
        int s, f;
        cin >> s >> f;
        sfs[s] = f;
    }

    cout << min_fights(n, p, sfs) << '\n';
    return 0;
}

// AJN 2022-01-20 https://contest.yandex.ru/snws2022/contest/23958/problems/C/
