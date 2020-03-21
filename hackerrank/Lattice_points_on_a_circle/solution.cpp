#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    os << ']';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const optional<T> o) {
    if (!o)
        os << "nullopt";
    else
        os << *o;

    return os;
}

using Int = long long;
const Int max_N = 100 * 1000 * 1000 * 1000LL; // 10¹¹

pair<vector<Int>, unordered_map<Int, Int>> primes_up_to(const Int x) {
    assert(x > 0);
    vector<bool> prime(x + 1, true);
    prime[0] = false;
    prime[1] = false;

    unordered_map<Int, Int> min_prime_factors_by_compound;

    for (Int i = 2; i <= x;) {
        for (Int k = 2; i * k <= x; ++k) {
            prime[i * k] = false;

            if (!min_prime_factors_by_compound.count(i * k)) {
                min_prime_factors_by_compound.insert({i * k, i});
            }
        }

        do {
            ++i;
        } while (i <= x && !prime[i]);
    }

    vector<Int> ans;

    for (Int i = 2; i != static_cast<Int>(prime.size()); ++i) {
        if (prime.at(i)) ans.push_back(i);
    }

    return {ans, min_prime_factors_by_compound};
}

vector<Int> factorize(unordered_map<Int, Int> min_prime_factors_by_compound,
                      Int m) {
    vector<Int> ans;

    while (min_prime_factors_by_compound.count(m)) {
        const Int p = min_prime_factors_by_compound.at(m);

        if (ans.size()) {
            assert(p != ans.back());
        }

        ans.push_back(p);
        m /= p;
    }

    if (ans.size()) {
        assert(m != ans.back());
    }

    if (m > 1) ans.push_back(m);

    return ans;
}

vector<Int> basis_powers(vector<Int> factorization) {
    transform(factorization.begin(), factorization.end(), factorization.begin(),
              [](const Int p) {
                  assert(p % 2 && p > 1);
                  return (p - 1) / 2;
              });

    return factorization;
}

optional<Int> exp_ltd(const Int base, const Int exponent, const Int max_val) {
    Int ans = 1;

    for (Int i = 0; i != exponent; ++i) {
        ans *= base;
        if (ans > max_val) return nullopt;
    }

    return ans;
}

vector<Int> solutions(const Int N, const Int m) { return {}; }

int main() {
    auto [primes, min_pf] = primes_up_to(static_cast<Int>(sqrt(max_N)));

    size_t q;
    cin >> q;

    for (auto i = 0U; i != q; ++i) {
        Int N, m;
        cin >> N >> m;
        cout << solutions(N, m).size() << '\n';
    }
}
