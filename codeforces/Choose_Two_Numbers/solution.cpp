#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;

    unordered_set<int> xs;

    for (int i = 0; i != n; ++i) {
        int x;
        cin >> x;
        xs.insert(x);
    }

    int m;
    cin >> m;

    unordered_set<int> ys;

    for (int i = 0; i != m; ++i) {
        int y;
        cin >> y;
        ys.insert(y);
    }

    for (const auto x : xs) {
        for (const auto y : ys) {
            if (!xs.count(x + y) && !xs.count(x + y)) {
                cout << x << ' ' << y << '\n';
                return 0;
            }
        }
    }

    return 0;
}
