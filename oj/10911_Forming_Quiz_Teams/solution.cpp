#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
static constexpr double INF = 1e18;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

double sum_of_distances(const vector<int> &matching_d2s) {
    double result{};
    for (const auto d2 : matching_d2s) {
        result += sqrt(0.0 + d2);
    }
    return result;
}

double solve(const vector<pii> &xy) {
    double result{INF};
    function<void(vector<int>)> recur;

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(2) << fixed;

    for (int tc = 1;; ++tc) {
        int N;
        cin >> N;
        if (!N) break;

        vector<pii> houses(2 * N);
        for (int i = 0; i < 2 * N; ++i) {
            string name;
            cin >> name;

            int x, y;
            cin >> x >> y;
            houses[i] = {x, y};
        }

        cout << "Case " << tc << ": " << solve(houses) << '\n';
    }

    return 0;
}
