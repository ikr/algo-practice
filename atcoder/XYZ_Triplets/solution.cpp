#include <bits/stdc++.h>
using namespace std;

constexpr int L = 1e4;

constexpr int f(const int x, const int y, const int z) {
    return x * x + y * y + z * z + x * y + y * z + x * z;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> counts(L + 1, 0);

    for (int x = 1; x <= L; ++x) {
        if (x * x > L) break;

        for (int y = 1; y <= L; ++y) {
            if (x * x + y * y + x * y > L) break;

            for (int z = 1; z <= L; ++z) {
                const auto res = f(x, y, z);
                if (res > L) break;
                ++counts[res];
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << counts[i] << '\n';
    }

    return 0;
}
