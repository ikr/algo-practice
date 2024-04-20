#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/rational.hpp>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using lll = boost::multiprecision::cpp_int;
using Ratio = boost::rational<lll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int solve_part_2(const int jump_distance) {
    ordered_set<pair<Ratio, int>> xs;
    xs.insert({Ratio(1'000'000), 0});
    xs.insert({Ratio(1'000'000'000), 1});

    int y{1};
    for (int x = 2, i = 1; x <= 50000000; ++x) {
        i += jump_distance + 1;
        i %= x;
        assert(x == sz(xs));

        const auto key_b = xs.find_by_order(i)->first;
        const auto key_a =
            (i == 0) ? (key_b - 1'000'000) : (xs.find_by_order(i - 1)->first);
        xs.insert({(key_a + key_b) / Ratio(2), x});

        if (x % 100'000 == 0) cerr << x << endl;

        const auto n = sz(xs);
        if (xs.find_by_order(((i + n - 1) % n))->second == 0) y = x;
    }
    return y;
}

int main() {
    int jump_distance;
    cin >> jump_distance;
    assert(jump_distance > 0);
    cout << solve_part_2(jump_distance) << '\n';
    return 0;
}
