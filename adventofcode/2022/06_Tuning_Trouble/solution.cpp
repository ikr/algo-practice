#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int uniques(const deque<int> &xs) { return sz(set(cbegin(xs), cend(xs))); }

int solution(const string &xs) {
    deque<int> q(cbegin(xs), cbegin(xs) + 14);
    if (uniques(q) == 14) return 14;

    for (int i = 14; i < sz(xs); ++i) {
        q.pop_front();
        q.push_back(xs[i]);
        if (uniques(q) == 14) return i + 1;
    }

    return 0;
}

int main() {
    string xs;
    cin >> xs;

    cout << solution(xs) << '\n';
    return 0;
}
