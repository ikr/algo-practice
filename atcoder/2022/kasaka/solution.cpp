#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string::size_type a_head_index(const string &xs) {
    if (xs[0] != 'a') return xs.npos;
    int i = 0;
    while (i < sz(xs) - 1 && xs[i + 1] == 'a') ++i;
    return i;
}

string::size_type a_tail_index(const string &xs) {
    if (xs.back() != 'a') return xs.npos;
    int i = sz(xs) - 1;
    while (i > 0 && xs[i - 1] == 'a') --i;
    return i;
}

bool is_palindrome(const string &xs) {
    auto ys = xs;
    reverse(begin(ys), end(ys));
    return xs == ys;
}

bool is_ok(const string &xs) {
    const auto i = a_head_index(xs);
    const auto h = i == xs.npos ? 0 : (i + 1);
    const auto j = a_tail_index(xs);
    const auto t = j == xs.npos ? 0 : (sz(xs) - j);

    if (h > t) return false;

    // cout << "i:" << i << " j:" << j << " h:" << h << " t:" << t
    //      << " l:" << (sz(xs) - h - t) << endl;
    return is_palindrome(xs.substr(h, sz(xs) - h - t));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;
    cout << (is_ok(xs) ? "Yes" : "No") << '\n';
    return 0;
}
