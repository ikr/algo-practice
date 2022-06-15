#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool tri_exists(const vector<int> &xs) {
    vector<int> fs(10, 0);
    for (const auto x : xs) ++fs[x % 10];

    for (int i = 0; i < sz(fs) - 2; ++i) {
        if (fs[i] >= 3 && ((3 * i) % 10) == 3) return true;

        for (int j = i + 1; j < sz(fs) - 1; ++j) {
            if (fs[i] >= 2 && fs[j] >= 1 && ((2 * i + j) % 10) == 3) {
                return true;
            }

            if (fs[i] >= 1 && fs[j] >= 2 && ((i + 2 * j) % 10) == 3) {
                return true;
            }

            for (int k = j + 1; k < sz(fs); ++k) {
                if (fs[k] >= 2 && fs[j] >= 1 && ((2 * k + j) % 10) == 3) {
                    return true;
                }

                if (fs[k] >= 1 && fs[j] >= 2 && ((k + 2 * j) % 10) == 3) {
                    return true;
                }

                if (fs[i] >= 2 && fs[k] >= 1 && ((2 * i + k) % 10) == 3) {
                    return true;
                }

                if (fs[i] >= 1 && fs[k] >= 2 && ((i + 2 * k) % 10) == 3) {
                    return true;
                }

                if (fs[i] && fs[j] && fs[k] && ((i + j + k) % 10) == 3) {
                    return true;
                }
            }
        }
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << (tri_exists(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
