#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const vector<int> xs{1,           10,           100,       1'000,
                         10'000,      100'000,      1'000'000, 10'000'000,
                         100'000'000, 1'000'000'000};

    int t;
    cin >> t;
    while (t--) {
        int m;
        cin >> m;

        for (int i = sz(xs) - 1; i >= 0; --i) {
            if (xs[i] <= m) {
                cout << (m - xs[i]) << '\n';
                break;
            }
        }
    }

    return 0;
}
