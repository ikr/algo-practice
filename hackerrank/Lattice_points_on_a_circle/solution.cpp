#define CATCH_CONFIG_MAIN
#include "catch.hpp"
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

vector<size_t> first_subvector_indices(const size_t sz) {
    vector<size_t> ans(sz);
    iota(ans.begin(), ans.end(), 0U);
    return ans;
}

optional<vector<size_t>> next_subvector_indices(const size_t sz,
                                                vector<size_t> indices) {
    assert(indices.size() > 0);
    bool bumped = false;

    for (auto i = indices.size() - 1; i-- != 0U;) {
        assert(indices.at(i) < sz);

        const auto max_here = sz - 1 - (indices.size() - 1 - i);

        if (indices[i] < max_here) {
            ++indices[i];
            bumped = true;
            break;
        }
    }

    return (bumped ? optional<vector<size_t>>(indices) : nullopt);
}

vector<Int> subvector(const vector<Int> &xs, const vector<size_t> &indices) {
    vector<Int> ans(indices.size());

    transform(indices.cbegin(), indices.cend(), ans.begin(),
              [&xs](const size_t i) {
                  assert(i < xs.size());
                  return xs.at(i);
              });

    return ans;
}

Int map_sum_solutions(const Int N, const Int m, const function<Int(Int)> map) {
    return map(0);
}

TEST_CASE("first_subvector_indices for size 3") {
    REQUIRE(first_subvector_indices(3) == vector<size_t>{0, 1, 2});
}

TEST_CASE("next_subvector_indices triple for the vector size of 4") {
    SECTION("first step") {
        const auto actual = next_subvector_indices(4, {0, 1, 2});
        REQUIRE(!!actual);
        REQUIRE(*actual == vector<size_t>{0, 1, 3});
    }

    SECTION("second step") {
        const auto actual = next_subvector_indices(4, {0, 1, 3});
        REQUIRE(!!actual);
        REQUIRE(*actual == vector<size_t>{0, 2, 3});
    }

    SECTION("third step") {
        const auto actual = next_subvector_indices(4, {0, 2, 3});
        REQUIRE(!!actual);
        REQUIRE(*actual == vector<size_t>{1, 2, 3});
    }

    SECTION("done") {
        const auto actual = next_subvector_indices(4, {1, 2, 3});
        REQUIRE(!actual);
    }
}

TEST_CASE("next_subvector_indices singleton for the vector size of 3") {
    SECTION("first step") {
        const auto actual = next_subvector_indices(3, {0});
        REQUIRE(!!actual);
        REQUIRE(*actual == vector<size_t>{1});
    }

    SECTION("second step") {
        const auto actual = next_subvector_indices(3, {1});
        REQUIRE(!!actual);
        REQUIRE(*actual == vector<size_t>{2});
    }

    SECTION("done") {
        const auto actual = next_subvector_indices(3, {2});
        REQUIRE(!actual);
    }
}

TEST_CASE("next_subvector_indices quad for the vector of size 100") {
    SECTION("split") {
        const auto actual = next_subvector_indices(100, {0, 1, 98, 99});
        REQUIRE(!!actual);
        REQUIRE(*actual == vector<size_t>{0, 2, 3, 4});
    }

    SECTION("spread") {
        const auto actual = next_subvector_indices(100, {3, 17, 56, 70});
        REQUIRE(!!actual);
        REQUIRE(*actual == vector<size_t>{3, 17, 56, 71});
    }

    SECTION("shifting the head") {
        const auto actual = next_subvector_indices(100, {66, 97, 98, 99});
        REQUIRE(!!actual);
        REQUIRE(*actual == vector<size_t>{67, 68, 69, 70});
    }

    SECTION("done") {
        const auto actual = next_subvector_indices(100, {96, 97, 98, 99});
        REQUIRE(!actual);
    }
}

// int main() {
//     auto [primes, min_pf] = primes_up_to(static_cast<Int>(sqrt(max_N)));

//     size_t q;
//     cin >> q;

//     for (auto i = 0U; i != q; ++i) {
//         Int N, m;
//         cin >> N >> m;
//         cout << solutions_count(N, m) << '\n';
//     }
// }
