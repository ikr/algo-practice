#include <bits/stdc++.h>
using namespace std;

constexpr bool all_differ(const int x, const int y, const int z) {
    return !(x == y || x == z || y == z);
}

constexpr bool is_triangle(const int x, const int y, const int z) {
    return x + y > z && x + z > y && y + z > x;
}

int count_triangles(const vector<int> &xs) {
    const int sz = xs.size();
    int ans = 0;

    for (int i = 0; i < sz - 2; ++i) {
        for (int j = i + 1; j < sz - 1; ++j) {
            for (int k = j + 1; k < sz; ++k) {
                if (all_differ(xs[i], xs[j], xs[k]) &&
                    is_triangle(xs[i], xs[j], xs[k])) {
                    ++ans;
                }
            }
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vector<int> xs(sz, 0);
    for (auto &x : xs) cin >> x;

    cout << count_triangles(xs) << '\n';

    return 0;
}
