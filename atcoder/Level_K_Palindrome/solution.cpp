#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

using Iter = string::const_iterator;

int diff_num(const Iter first, const Iter last) {
    if (distance(first, last) < 2) return 0;

    int ans = 0;
    Iter l = first;
    Iter r = prev(last);

    while (l < r) {
        if (*l != *r) ++ans;
        ++l;
        --r;
    }

    return ans;
}

int recur(const int togo, const Iter z, const Iter first, const Iter last) {
    cerr << "togo:" << togo << " first:" << distance(z, first)
         << " last:" << distance(z, last) << '\n';

    if (first == last) return togo == 0 ? 0 : -1;
    if (distance(first, last) == 1) return togo == 1 ? 0 : -1;

    const int d = inof(distance(first, last));
    const Iter mid = first + d / 2;

    const int sub_left = recur(togo - 1, z, first, mid);
    if (sub_left == -1) return -1;

    const int sub_right = recur(togo - 1, z, mid + 1, last);
    if (sub_right == -1) return -1;

    return togo == 0 ? diff_num(first, last)
                     : diff_num(first, last) + sub_left + sub_right;
}

int min_ops(const int k, const string &xs) {
    return recur(k, cbegin(xs), cbegin(xs), cend(xs));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int k;
    cin >> k;

    string xs;
    cin >> xs;

    const int ans = min_ops(k, xs);
    cout << (ans >= 0 ? to_string(ans) : "impossible") << '\n';
    return 0;
}
