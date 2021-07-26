#include <bits/stdc++.h>

using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    const auto i_back = prev(cend(xs));

    for (auto i = cbegin(xs); i != cend(xs); ++i) {
        os << *i;
        if (i != i_back) os << ' ';
    }

    return os;
}

vector<int>::size_type zeros_count_with_replace(vector<int> &xs) {
    vector<int>::size_type zeros_count = 0;

    for (int &x : xs) {
        if (!x) {
            ++zeros_count;
            x = -1;
        }
    }

    return zeros_count;
}

void compute(vector<int> &xs) {
    const auto zeros_count = zeros_count_with_replace(xs);

    if (zeros_count == xs.size()) {
        if (xs.size() % 2) {
            fill(begin(xs), end(xs), 0);
            return;
        }

        fill(begin(xs), end(xs), -1);
        return;
    }

    const bool all_negative =
        all_of(cbegin(xs), cend(xs), [](const int x) { return x < 0; });

    if (all_negative) {
        if (xs.size() % 2 == 0) return;

        auto i_min = min_element(begin(xs), end(xs));
        *i_min = -(*i_min) - 1;
        return;
    }

    int sign = 1;
    for (int &x : xs) {
        if (x > 0) x = -x - 1;
        sign *= (x < 0 ? -1 : 1);
    }

    if (sign < 0) {
        auto i_min = min_element(begin(xs), end(xs));
        *i_min = -(*i_min) - 1;
    }
}

void do_io() {
    int sz;
    cin >> sz;
    vector<int> xs(sz);
    for (int i = 0; i != sz; ++i) {
        int x;
        cin >> x;
        xs[i] = x;
    }

    compute(xs);
    cout << xs << '\n';
}

int main() {
    do_io();
    return 0;
}
