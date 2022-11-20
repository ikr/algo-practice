#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_guaranteed(int L, const vector<int> &xs) {
    for (const auto x : xs) {
        if (x == 1) {
            if (L >= 2) {
                L -= 2;
            }
        } else {
            assert(x == 2);
            if (L < 2) return false;

            if (L >= 3) {
                L -= 3;
            } else if (L == 2) {
                L = 0;
            }
        }
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, L;
    cin >> N >> L;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << (is_guaranteed(L, xs) ? "Yes" : "No") << '\n';
    return 0;
}
