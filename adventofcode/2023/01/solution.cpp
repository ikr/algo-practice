#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    int result{};
    for (string line; getline(cin, line);) {
        string cur;
        for (const char c : line) {
            if ('0' <= c && c <= '9') cur += c;
        }

        assert(!empty(cur));
        string src{cur[0], cur.back()};
        result += stoi(src);
    }
    cout << result << '\n';
    return 0;
}
