#include <iostream>
#include <map>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int find_triple_x(const vector<int> &xs) {
    map<int, int> fs;
    for (const auto x : xs) ++fs[x];

    for (const auto [k, v] : fs) {
        if (v >= 3) return k;
    }

    return -1;
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

        cout << find_triple_x(xs) << '\n';
    }

    return 0;
}
