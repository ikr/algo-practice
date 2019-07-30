#include <bits/stdc++.h>

using namespace std;

template <typename T> int intof(const T x) { return static_cast<int>(x); }

int find_day(const vector<int> &ays, const int x, const int y) {
    for (int d = 0; d != intof(ays.size()); ++d) {
        bool ok = true;

        for (int i = d - x; i < d && i >= 0; ++i) {
            if (ays[i] < ays[d]) {
                ok = false;
                break;
            }
        }

        if (!ok) continue;

        for (int i = d + 1; i <= d + y && i < intof(ays.size()); ++i) {
            if (ays[i] < ays[d]) {
                ok = false;
                break;
            }
        }

        if (ok) return d;
    }

    return -1;
}

int main() {
    int n;
    int x;
    int y;
    cin >> n >> x >> y;

    vector<int> ays(n);
    for (auto &a : ays) {
        cin >> a;
    }

    cout << find_day(ays, x, y) + 1 << '\n';
    return 0;
}
