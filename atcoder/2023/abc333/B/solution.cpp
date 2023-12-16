#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

constexpr int dist(const int X, const int Y) {
    if (X == Y) return 0;

    if (X == 0 && Y == 1) return 1;
    if (X == 0 && Y == 2) return 2;
    if (X == 0 && Y == 3) return 2;
    if (X == 0 && Y == 4) return 1;

    if (X == 1 && Y == 2) return 1;
    if (X == 1 && Y == 3) return 2;
    if (X == 1 && Y == 4) return 2;

    if (X == 2 && Y == 3) return 1;
    if (X == 2 && Y == 4) return 2;

    if (X == 3 && Y == 4) return 1;

    assert(false);
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xy;
    cin >> xy;

    string pq;
    cin >> pq;

    array XY{inof(xy[0] - 'A'), inof(xy[1] - 'A')};
    array PQ{inof(pq[0] - 'A'), inof(pq[1] - 'A')};

    ranges::sort(XY);
    ranges::sort(PQ);

    const auto yes = [&]() -> bool {
        vector<int> common;
        const auto dxy = dist(XY[0], XY[1]);
        const auto dpq = dist(PQ[0], PQ[1]);
        return dxy == dpq;
    }();
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
