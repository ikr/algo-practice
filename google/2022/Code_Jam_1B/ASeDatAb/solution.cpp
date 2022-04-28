#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <string>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string rotop(string xs, const int r) {
    assert(0 <= r && r < 8);
    assert(sz(xs) == 8);
    rotate(begin(xs), prev(end(xs), r), end(xs));
    return xs;
}

bool interrogate() { return false; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    assert(rotop("00110011", 5) == "10011001");
    assert(rotop("10000001", 0) == "10000001");
    assert(rotop("00000001", 1) == "10000000");
    assert(rotop("00000001", 7) == "00000010");

    int t;
    cin >> t;
    while (t--) {
        if (!interrogate()) break;
    }

    return 0;
}
