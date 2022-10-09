#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pii> candidate_ranges(const string &xs) {
    vector<pii> result;
    optional<int> a;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '0') {
            if (a) {
                assert(i > 0);
                result.emplace_back(*a, i - 1);
                a = nullopt;
            }
        } else {
            if (!a) {
                a = i;
            }
        }
    }

    if (a) {
        result.emplace_back(*a, sz(xs) - 1);
    }

    return result;
}

int leading_qs_num(const string &xs, int i) {
    if (xs[i] != '?') return 0;
    int result = 1;

    while (i + 1 < sz(xs) && xs[i + 1] == '?') {
        ++result;
        ++i;
    }

    return result;
}

int trailing_qs_num(const string &xs, int i) {
    if (xs[i] != '?') return 0;
    int result = 1;

    while (i - 1 >= 0 && xs[i - 1] == '?') {
        ++result;
        --i;
    }

    return result;
}

bool is_possible_on(const string &xs, const int K, const pii ab) {
    const auto [a, b] = ab;
    const auto m = b - a + 1;
    if (m < K) return false;
    if (m == K) return true;

    assert(m > K);

    const auto vl = leading_qs_num(xs, a);
    const auto vr = trailing_qs_num(xs, b);
    if (vl == 0 && vr == 0) return false;

    if (vl == m) {
        assert(vr == m);
        return false;
    }

    assert(vl + vr < m);

    if (m - vl - vr > K) return false;
    if (m - vl - vr == K) return true;

    return vl == 0 || vr == 0;
}

bool is_possible(const string &xs, const int K) {
    const auto is_long_enough = [K](const pii ab) {
        return ab.second - ab.first + 1 >= K;
    };

    const auto contains_a_one = [&xs](const pii ab) {
        return any_of(cbegin(xs) + ab.first, cbegin(xs) + ab.second + 1,
                      [](const char x) { return x == '1'; });
    };

    const auto rs = candidate_ranges(xs);
    const auto containing_one_num =
        count_if(cbegin(rs), cend(rs), contains_a_one);

    if (containing_one_num > 1) return false;
    if (containing_one_num == 1) {
        return is_possible_on(xs, K,
                              *find_if(cbegin(rs), cend(rs), contains_a_one));
    }

    const auto long_enough_num = count_if(cbegin(rs), cend(rs), is_long_enough);

    if (long_enough_num != 1) return false;
    return is_possible_on(xs, K,
                          *find_if(cbegin(rs), cend(rs), is_long_enough));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;

        string xs;
        cin >> xs;
        assert(sz(xs) == N);

        cout << (is_possible(xs, K) ? "Yes" : "No") << '\n';
    }

    return 0;
}
