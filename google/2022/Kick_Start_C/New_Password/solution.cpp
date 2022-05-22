#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string solve(string xs) {
    if (none_of(cbegin(xs), cend(xs), [](const char x) {
            return inof('A') <= inof(x) && inof(x) <= inof('Z');
        })) {
        xs += 'A';
    }

    if (none_of(cbegin(xs), cend(xs), [](const char x) {
            return inof('a') <= inof(x) && inof(x) <= inof('z');
        })) {
        xs += 'a';
    }

    if (none_of(cbegin(xs), cend(xs), [](const char x) {
            return inof('0') <= inof(x) && inof(x) <= inof('9');
        })) {
        xs += '0';
    }

    const set<char> SP{'#', '@', '*', '&'};
    if (none_of(cbegin(xs), cend(xs),
                [&SP](const char x) -> bool { return SP.count(x); })) {
        xs += '#';
    }

    if (sz(xs) < 7) {
        const auto d = 7 - sz(xs);
        xs += string(d, 'A');
    }

    return xs;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        string xs;
        cin >> xs;
        assert(sz(xs) == N);

        cout << "Case #" << i << ": " << solve(move(xs)) << '\n';
    }

    return 0;
}
