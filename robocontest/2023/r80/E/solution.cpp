#include <bits/stdc++.h>
using namespace std;

using Box = array<array<int, 3>, 3>;

static const Box Dst{array{1, 2, 3}, array{4, 5, 6}, array{7, 8, 9}};

set<Box> adjacent_boxes(const Box &b) {
    set<Box> result;

    for (int ro = 0; ro < 3; ++ro) {
        for (int co = 0; co < 3; ++co) {
            if (ro) {
                auto v = b;
                swap(v[ro][co], v[ro - 1][co]);
                result.insert(v);
            }
            if (co < 2) {
                auto v = b;
                swap(v[ro][co], v[ro][co + 1]);
                result.insert(v);
            }
            if (ro < 2) {
                auto v = b;
                swap(v[ro][co], v[ro + 1][co]);
                result.insert(v);
            }
            if (co) {
                auto v = b;
                swap(v[ro][co], v[ro][co - 1]);
                result.insert(v);
            }
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    Box Src{};
    for (auto &row : Src) {
        for (auto &x : row) cin >> x;
    }

    map<Box, int> D;
    D[Src] = 0;

    queue<Box> q;
    q.push(Src);

    while (!D.count(Dst)) {
        const auto u = q.front();
        q.pop();

        for (const auto &v : adjacent_boxes(u)) {
            if (D.count(v)) continue;
            D[v] = D.at(u) + 1;
            q.push(v);
        }
    }

    cout << D.at(Dst) << '\n';
    return 0;
}
