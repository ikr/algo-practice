#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using pii = pair<int, int>;

constexpr bool intersect(const pii x, const pii y) {
    const auto [a, b] = x;
    const auto [i, j] = y;
    return !(b < i || j < a);
}

pii union_of(const pii x, const pii y) {
    assert(intersect(x, y));
    set<int> points{x.first, x.second, y.first, y.second};
    return {*cbegin(points), *crbegin(points)};
}

void join_in(set<pii> &AB, pii xy) {
    for (;;) {
        auto it = AB.lower_bound(pii{xy.second, xy.second});
        if (!AB.empty() && it != cbegin(AB)) it = prev(it);

        if (it != cend(AB) && intersect(xy, *it)) {
            const auto [p, q] = *it;
            AB.erase(it);

            const auto xy_ = union_of(xy, {p, q});
            xy = xy_;
        } else {
            AB.insert(xy);
            break;
        }
    }
}

vector<pii> merge_adjacent(const set<pii> &AB) {
    vector<pii> result;

    for (const auto &[a, b] : AB) {
        if (result.empty()) {
            result.emplace_back(a, b);
        } else {
            const auto [i, j] = result.back();

            if (j + 1 == a) {
                result.back().second = b;
            } else {
                result.emplace_back(a, b);
            }
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;
    vector<pii> LR(N);
    for (auto &[L, R] : LR) cin >> L >> R;
    sort(begin(LR), end(LR));

    set<pii> AB;
    for (int i = 0; i < N; ++i) {
        const auto [L, R] = LR[i];
        join_in(AB, {L, R - 1});
    }

    for (const auto &[a, b] : merge_adjacent(AB)) {
        cout << a << ' ' << (b + 1) << '\n';
    }
    return 0;
}
