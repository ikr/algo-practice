#include <bits/stdc++.h>

using namespace std;

template <typename Iter>
Iter is_strictly_ascending_until(const Iter first, const Iter last) {
    Iter i = first;
    if (i == last) return last;

    Iter next = i + 1;

    while (next != last && *next > *i && *next != *i) {
        ++i;
        ++next;
    }

    return next;
}

int main() {
    int n;
    cin >> n;

    vector<int> xs(n);

    for (int i = 0; i != n; ++i) {
        int x;
        cin >> x;

        xs[i] = x;
    }

    size_t result = 0;
    auto i = xs.begin();
    while (i != xs.end()) {
        auto ii = is_strictly_ascending_until(i, xs.end());
        const size_t candidate = distance(i, ii);
        if (candidate > result) result = candidate;
        i = ii;
    }

    cout << result << '\n';
}
