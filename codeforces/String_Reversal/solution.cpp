#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr int SZ = 'z' - 'a' + 1;

namespace atcoder {
namespace internal {
template <class T>
using is_signed_int128 = typename conditional<is_same<T, __int128_t>::value ||
                                                  is_same<T, __int128>::value,
                                              true_type, false_type>::type;

template <class T>
using is_unsigned_int128 =
    typename conditional<is_same<T, __uint128_t>::value ||
                             is_same<T, unsigned __int128>::value,
                         true_type, false_type>::type;

template <class T>
using make_unsigned_int128 =
    typename std::conditional<is_same<T, __int128_t>::value, __uint128_t,
                              unsigned __int128>;

template <class T>
using is_integral =
    typename conditional<is_integral<T>::value || is_signed_int128<T>::value ||
                             is_unsigned_int128<T>::value,
                         true_type, false_type>::type;

template <class T>
using is_signed_int =
    typename conditional<(is_integral<T>::value && is_signed<T>::value) ||
                             is_signed_int128<T>::value,
                         true_type, false_type>::type;

template <class T>
using is_unsigned_int =
    typename conditional<(is_integral<T>::value && is_unsigned<T>::value) ||
                             is_unsigned_int128<T>::value,
                         true_type, false_type>::type;

template <class T>
using to_unsigned = typename conditional<
    is_signed_int128<T>::value, make_unsigned_int128<T>,
    typename conditional<is_signed<T>::value, make_unsigned<T>,
                         common_type<T>>::type>::type;

template <class T> using is_signed_int_t = enable_if_t<is_signed_int<T>::value>;

template <class T>
using is_unsigned_int_t = enable_if_t<is_unsigned_int<T>::value>;

template <class T> using to_unsigned_t = typename to_unsigned<T>::type;
} // namespace internal

// Reference: https://en.wikipedia.org/wiki/Fenwick_tree
template <class T> struct fenwick_tree {
    using U = internal::to_unsigned_t<T>;

  public:
    fenwick_tree() : _n(0) {}
    fenwick_tree(int n) : _n(n), data(n) {}

    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p - 1] += U(x);
            p += p & -p;
        }
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

  private:
    int _n;
    vector<U> data;

    U sum(int r) {
        U s = 0;
        while (r > 0) {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }
};

} // namespace atcoder

string reversed(string s) {
    reverse(begin(s), end(s));
    return s;
}

vector<int> permutation_of_reversed(const string &s) {
    const auto rs = reversed(s);
    const int n = s.size();
    vector<int> ans(n, -1);
    vector<deque<int>> idx(SZ);

    for (int i = 0, j = 0; i < n;) {
        const char x = s[i];
        const char y = rs[j];

        idx[y - 'a'].push_back(j);

        if (!idx[x - 'a'].empty()) {
            ans[i] = idx[x - 'a'].front();
            idx[x - 'a'].pop_front();
            ++i;
        }

        if (j < n - 1) ++j;
    }

    return ans;
}

ll count_inversions(const vector<int> &xs) {
    const int n = xs.size();
    ll ans = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (xs[i] > xs[j]) ++ans;
        }
    }

    return ans;
}

ll min_swaps(const string &s) {
    return count_inversions(permutation_of_reversed(s));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    string s(n, ' ');
    cin >> s;

    cout << min_swaps(s) << '\n';
    return 0;
}
