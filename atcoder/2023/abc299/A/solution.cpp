#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;
    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    const auto ia = xs.find('|');
    const auto is = xs.find('*');
    const auto ib = xs.find('|', ia + 1);

    const auto in = (ia < is && is < ib);
    cout << (in ? "in" : "out") << '\n';
    return 0;
}
