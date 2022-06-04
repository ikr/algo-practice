#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const int K, vector<int> xs) {
    if (K == 1) return true;

    for (int i = 0; i + K < sz(xs); ++i) {
        if (xs[i] > xs[i + K]) {
            swap(xs[i], xs[i + K]);
        }
    }

    for (int j = sz(xs) - 1; j - K >= 0; --j) {
        if (xs[j - K] > xs[j]) {
            swap(xs[j - K], xs[j]);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, K;
    cin >> N >> K;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << (is_possible(K, move(xs)) ? "Yes" : "No") << '\n';
    return 0;
}
