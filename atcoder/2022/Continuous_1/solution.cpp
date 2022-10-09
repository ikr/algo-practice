#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const optional<T> o) {
    if (!o) {
        os << "nullopt";
    } else {
        os << *o;
    }
    return os;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_statically_clustered(const string &xs) {
    optional<int> lo1;
    optional<int> hi1;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '1') {
            if (!lo1) {
                lo1 = i;
                hi1 = i;
            } else {
                hi1 = i;
            }
        }
    }
    if (!lo1) return false;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '0' && !(i < *lo1 || *hi1 < i)) {
            return true;
        }
    }

    return false;
}

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

bool is_possible(const string &xs, const int K) {
    if (is_statically_clustered(xs)) return false;

    const auto is_long_enough = [K](const pii &ab) {
        return ab.second - ab.first + 1 >= K;
    };

    const auto rs = candidate_ranges(xs);
    const auto long_enough_num = count_if(cbegin(rs), cend(rs), is_long_enough);

    if (long_enough_num != 1) return false;
    const auto it = find_if(cbegin(rs), cend(rs), is_long_enough);

    const auto [a, b] = *it;
    if (a == b) {
        assert(K == 1);
        return true;
    }

    const auto m = b - a + 1;
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
