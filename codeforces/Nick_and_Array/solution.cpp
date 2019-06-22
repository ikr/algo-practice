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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xs) {
    for (const auto &x : xs) {
        os << '[' << x << "] ";
    }

    return os;
}

//------------------------------------------------------------------------------

void indices_subsets(const size_t sz, const vector<size_t> &prefix,
                     const size_t index, vector<vector<size_t>> &result) {
    if (index == sz) {
        result.push_back(prefix);
        return;
    }

    indices_subsets(sz, prefix, index + 1, result);

    vector<size_t> prefix_with = prefix;
    prefix_with.push_back(index);
    indices_subsets(sz, prefix_with, index + 1, result);
}

ll_t mul(const vector<ll_t> &xs) {
    return accumulate(xs.begin(), xs.end(), 1, multiplies<ll_t>());
}

vector<ll_t> bruteforce_swaps_max_product(const vector<ll_t> &xs) {
    vector<vector<size_t>> idx_sets;
    indices_subsets(xs.size(), {}, 0, idx_sets);

    ll_t optimum = numeric_limits<ll_t>::min();
    vector<ll_t> result;

    for (const auto &idxs : idx_sets) {
        vector<ll_t> xs_copy = xs;
        for (const auto idx : idxs) {
            xs_copy[idx] = -xs_copy[idx] - 1;
        }

        const ll_t candidate = mul(xs_copy);
        if (candidate > optimum) {
            result = xs_copy;
            optimum = candidate;
        }
    }

    return result;
}

vector<ll_t> random_vector(const size_t sz, const unsigned int magnitude) {
    random_device rd;
    uniform_int_distribution<int> dist(-magnitude, magnitude);

    vector<ll_t> result(sz);
    generate(result.begin(), result.end(), [&dist, &rd]() { return dist(rd); });
    return result;
}

//------------------------------------------------------------------------------

int zeros_count_with_replace(vector<ll_t> &xs) {
    int zeroes_count = 0;

    for (auto &x : xs) {
        if (x == 0LL) {
            ++zeroes_count;
            x = -1;
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
        if (x > 0) x = -x - 1LL;
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

void compare_to_bruteforce_results() {
    for (int i = 0; i != 1000000; ++i) {
        const vector<ll_t> xs = random_vector(10, 10);
        const auto opt_prod = bruteforce_swaps_max_product(xs);

        vector<ll_t> xs_copy = xs;
        compute(xs_copy);

        if (mul(xs_copy) != mul(opt_prod)) {
            cout << "failure on " << xs << '\n';
            cout << "computed is " << xs_copy << '\n';
            cout << "optimal is " << opt_prod << '\n';
            break;
        }
    }
}

int main() {
    // do_io();
    compare_to_bruteforce_results();
    return 0;
}
