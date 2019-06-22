#include <bits/stdc++.h>

using namespace std;

using ll_t = long long;
template <typename T> int intof(const T x) { return static_cast<int>(x); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    const auto i_back = xs.end() - 1;

    for (auto i = xs.begin(); i != xs.end(); ++i) {
        os << *i;
        if (i != i_back) os << ' ';
    }

    return os;
}

int zeros_count_with_replace(vector<ll_t> &xs) {
    int zeroes_count = 0;

    for (auto &x : xs) {
        if (x == 0LL) {
            ++zeroes_count;
            x = -1LL;
        }
    }

    return zeroes_count;
}

vector<ll_t>::iterator min_positive_element(vector<ll_t> &xs) {
    vector<ll_t>::iterator result = xs.end();
    ll_t value = numeric_limits<ll_t>::max();

    for (auto i = xs.begin(); i != xs.end(); ++i) {
        if (*i > 0LL && *i < value) {
            result = i;
            value = *i;
        }
    }

    return result;
}

void compute(vector<ll_t> &xs) {
    const int zeros_count = zeros_count_with_replace(xs);

    if (zeros_count == intof(xs.size())) {
        if (xs.size() % 2) {
            fill(xs.begin(), xs.end(), 0LL);
            return;
        }

        fill(xs.begin(), xs.end(), -1LL);
        return;
    }

    const bool all_negative =
        all_of(xs.begin(), xs.end(), [](const auto x) { return x < 0LL; });

    if (all_negative) {
        if (xs.size() % 2 == 0) return;

        auto i_min = min_element(xs.begin(), xs.end());
        *i_min = -(*i_min) - 1LL;
        return;
    }

    auto i_max = min_positive_element(xs);
    const ll_t v_max = *i_max;

    int sign = 1;
    for (auto &x : xs) {
        if (x > 0LL) x = -x - 1LL;
        sign *= (x < 0LL ? -1 : 1);
    }

    if (sign < 0) *i_max = v_max;
}

void do_io() {
    int sz;
    cin >> sz;
    vector<ll_t> xs(sz);
    for (int i = 0; i != sz; ++i) {
        ll_t x;
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
