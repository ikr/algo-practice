#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int INF = 1'000'000'000;
static constexpr int WIN = 0;
static constexpr int TIE = 1;
static constexpr int LOS = 2;

int max_score(vector<int> xs, vector<int> ys) {
    sort(begin(xs), end(xs));
    sort(begin(ys), end(ys));

    vector<array<int, 3>> score(sz(ys));
    for (auto &row : score) row.fill(-INF);

    vector<array<multiset<int>, 3>> xss(sz(ys));
    for (auto &row : xss) row.fill({});

    { // WIN
        const auto it = upper_bound(cbegin(xs), cend(xs), ys[0]);
        if (it != cend(xs)) {
            score[0][WIN] = 1;
            xss[0][WIN] = multiset<int>(cbegin(xs), cend(xs));
            xss[0][WIN].erase(xss[0][WIN].find(*it));
        }
    }

    { // TIE
        const auto it = lower_bound(cbegin(xs), cend(xs), ys[0]);
        if (it != cend(xs) && *it == ys[0]) {
            score[0][TIE] = 0;
            xss[0][TIE] = multiset<int>(cbegin(xs), cend(xs));
            xss[0][TIE].erase(xss[0][TIE].find(*it));
        }
    }

    { // LOS
        auto it = lower_bound(cbegin(xs), cend(xs), ys[0]);
        if (it != cbegin(xs)) {
            const auto jt = lower_bound(cbegin(xs), cend(xs), *prev(it));
            assert(jt != cend(xs));

            score[0][LOS] = -1;
            xss[0][LOS] = multiset<int>(cbegin(xs), cend(xs));
            xss[0][LOS].erase(xss[0][LOS].find(*jt));
        }
    }

    for (int i = 1; i < sz(score); ++i) {
        for (int j = 0; j < 3; ++j) {
            if (score[i - 1][j] == -INF) continue;
            auto cur = xss[i - 1][j];

            { // WIN
                const auto it = upper_bound(cbegin(cur), cend(cur), ys[i]);
                if (it != cend(cur) && score[i - 1][j] + 1 > score[i][WIN]) {
                    score[i][WIN] = score[i - 1][j] + 1;
                    xss[i][WIN] = cur;
                    xss[i][WIN].erase(xss[i][WIN].find(*it));
                }
            }

            { // TIE
                const auto it = lower_bound(cbegin(cur), cend(cur), ys[i]);
                if (it != cend(cur) && *it == ys[i] &&
                    score[i - 1][j] > score[i][TIE]) {
                    score[i][TIE] = score[i - 1][j];
                    xss[i][TIE] = cur;
                    xss[i][TIE].erase(xss[i][TIE].find(*it));
                }
            }

            { // LOS
                auto it = lower_bound(cbegin(cur), cend(cur), ys[i]);
                if (it != cbegin(cur) && score[i - 1][j] - 1 > score[i][LOS]) {
                    const auto jt =
                        lower_bound(cbegin(cur), cend(cur), *prev(it));
                    assert(jt != cend(cur));

                    score[i][LOS] = score[i - 1][j] - 1;
                    xss[i][LOS] = cur;
                    xss[i][LOS].erase(xss[i][LOS].find(*jt));
                }
            }
        }
    }

    return *max_element(cbegin(score.back()), cend(score.back()));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    vector<int> ys(n);
    for (auto &y : ys) cin >> y;

    cout << max_score(move(xs), move(ys)) << '\n';
    return 0;
}
