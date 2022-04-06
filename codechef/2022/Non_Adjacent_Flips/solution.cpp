#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_ops(const string &xs) {
    vector<int> idx;
    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '1') idx.push_back(i);
    }
    if (idx.empty()) return 0;

    for (int i = 1; i < sz(idx); ++i) {
        if (idx[i - 1] + 1 == idx[i]) return 2;
    }

    return 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        string xs;
        cin >> xs;
        assert(sz(xs) == N);

        cout << min_ops(xs) << '\n';
    }

    return 0;
}
