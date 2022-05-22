#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

using vi = vector<int>;

enum class Dir { LEFT = 0, RIGHT = 1 };
using Ant = pair<int, Dir>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

void flip_ant(Ant &a) {
    if (a.second == Dir::LEFT) {
        a.second = Dir::RIGHT;
    } else {
        a.second = Dir::LEFT;
    }
}

vi solve(const int L, vector<Ant> ants) {
    deque<int> q(sz(ants));
    iota(begin(q), end(q), 0);
    sort(begin(q), end(q),
         [&](const int i, const int j) -> bool { return ants[i] < ants[j]; });

    vi result;
    result.reserve(sz(ants));

    while (!q.empty()) {
        for (const auto i : q) {
            if (ants[i].second == Dir::LEFT) {
                --(ants[i].first);
            } else {
                ++(ants[i].first);
            }
        }

        set<int> fallen;
        if (ants[q.front()].first == 0) {
            fallen.insert(q.front());
            q.pop_front();
        }
        if (!q.empty() && ants[q.back()].first == L) {
            fallen.insert(q.back());
            q.pop_back();
        }
        result.insert(end(result), cbegin(fallen), cend(fallen));

        for (int j = 1; j < sz(q);) {
            if (ants[q[j - 1]].first == ants[q[j]].first) {
                flip_ant(ants[q[j - 1]]);
                flip_ant(ants[q[j]]);
                j += 2;
            } else {
                ++j;
            }
        }
    }

    return result;
}

void print_answer(const vi &indices) {
    for (auto i = indices.cbegin(); i != indices.cend(); ++i) {
        if (i != indices.cbegin()) cout << ' ';
        cout << ((*i) + 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, L;
        cin >> N >> L;
        L *= 2;

        vector<Ant> ants(N);
        for (auto &[x, d] : ants) {
            cin >> x;
            x *= 2;

            int y;
            cin >> y;
            d = y ? Dir::RIGHT : Dir::LEFT;
        }

        cout << "Case #" << i << ": ";
        print_answer(solve(L, move(ants)));
        cout << '\n';
    }

    return 0;
}
