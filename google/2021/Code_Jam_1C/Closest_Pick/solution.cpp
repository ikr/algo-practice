#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

enum class Snap { L, R };

struct Placement final {
    pii interval;
    Snap snap;
};

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

ostream &operator<<(ostream &os, const Placement &p) {
    if (p.snap == Snap::L) {
        os << '*' << p.interval;
    } else {
        os << p.interval << '*';
    }

    return os;
}

int winning_places_num(const int k, const Placement &p) {
    const auto [a, b] = p.interval;
    return (a == 0 || b > k) ? (b - a - 1) : ((b - a) / 2);
}

int winning_places_num(const int k, const Placement &p1, const Placement &p2) {
    if (p1.interval != p2.interval) {
        return winning_places_num(k, p1) + winning_places_num(k, p2);
    }

    if (p1.snap == p2.snap) return winning_places_num(k, p1);

    const auto [a, b] = p1.interval;
    return b - a + 1 - 2;
}

double solve(const int k, const vi &xs) {
    int best_wins = 0;

    for (int i = 0; i < sz(xs) - 1; ++i) {
        for (int j = i; j < sz(xs) - 1; ++j) {
            const pii interval1{xs[i], xs[i + 1]};
            const pii interval2{xs[j], xs[j + 1]};

            for (const auto snap1 : {Snap::L, Snap::R}) {
                for (const auto snap2 : {Snap::L, Snap::R}) {
                    const auto wins = winning_places_num(k, {interval1, snap1},
                                                         {interval2, snap2});

                    // cerr << "p1: " << Placement{interval1, snap1}
                    //      << " p2: " << Placement{interval2, snap2}
                    //      << " wins: " << wins << endl;

                    best_wins = max(best_wins, wins);
                }
            }
        }
    }

    return doof(best_wins) / doof(k);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(7) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n, k;
        cin >> n >> k;

        vi xs(n);
        for (auto &x : xs) cin >> x;
        xs.push_back(0);
        xs.push_back(k + 1);

        sort(begin(xs), end(xs));
        xs.erase(unique(begin(xs), end(xs)), end(xs));

        cout << "Case #" << i << ": " << solve(k, xs) << '\n';
    }

    return 0;
}
