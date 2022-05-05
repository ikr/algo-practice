#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<vector<int>, vector<int>> index_zos(const string &xs) {
    vector<int> zs;
    vector<int> os;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '0') zs.push_back(i);
        if (xs[i] == '1') os.push_back(i);
    }

    return {zs, os};
}

int num_suspects(string xs) {
    if (sz(xs) == 1 || xs[0] == '0' || xs.back() == '1') return 1;
    xs[0] = '1';
    xs.back() = '0';

    const auto [zs, os] = index_zos(xs);
    if (sz(zs) == 1 && sz(os) == 1) return sz(xs);
    if (sz(zs) > 1 && sz(os) > 1) return zs[0] - os.back() + 1;
    if (sz(os) == 1) return zs[0] + 1;
    if (sz(zs) == 1) return os.back() + 1;

    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << num_suspects(move(xs)) << '\n';
    }

    return 0;
}
