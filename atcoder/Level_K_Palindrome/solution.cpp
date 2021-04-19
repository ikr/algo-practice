#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

using Iter = string::iterator;

array<int, 26> freqs(const Iter first, const Iter last) {
    array<int, 26> ans{};
    for (auto it = first; it != last; ++it) ++ans[*it - 'a'];
    return ans;
}

bool is_palindrome(const Iter first, const Iter last) {
    const string xs(first, last);
    string ys(first, last);
    reverse(begin(ys), end(ys));
    return xs == ys;
}

void bump(char &c) {
    const int x = (c - 'a' + 1) % 26;
    c = static_cast<char>('a' + x);
}

int min_ops_recur(const int level, const int multiplier, const Iter z,
                  const pair<Iter, Iter> range) {
    const auto [first, last] = range;
    const int d = inof(distance(first, last));
    if (d == 0) return level == 0 ? 0 : -1;

    if (level == 0) {
        if (d == 1) return -1;

        if (is_palindrome(first, last)) {
            bump(*first);
            return multiplier;
        }

        return 0;
    }

    Iter l = first;
    Iter r = prev(last);

    int ops = 0;
    while (l < r) {
        if (*l != *r) {
            *l = *r;
            ops += multiplier;
        }

        ++l;
        --r;
    }

    const auto mid = first + d / 2;
    const auto sub = min_ops_recur(level - 1, multiplier * 2, z, {first, mid});
    if (sub == -1) return -1;

    return ops + sub;
}

int min_ops(const int k, string xs) {
    return min_ops_recur(k, 1, begin(xs), {begin(xs), end(xs)});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int k;
    cin >> k;

    string xs;
    cin >> xs;

    const int ans = min_ops(k, move(xs));
    cout << (ans >= 0 ? to_string(ans) : "impossible") << '\n';
    return 0;
}
