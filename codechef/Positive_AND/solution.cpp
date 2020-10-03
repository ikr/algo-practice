#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

constexpr bool is_pow2(const int x) { return __builtin_popcount(x) == 1; }

vector<int> beautiful_permutation(const int n) {
    if (n == 1) return {1};
    if (is_pow2(n)) return {-1};
    vector<int> ans{2, 3, 1};
    ans.reserve(n);

    for (int i = 4; i <= n; ++i) {
        if (is_pow2(i)) {
            ans.push_back(i + 1);
            ans.push_back(i);
            ++i;
        } else {
            ans.push_back(i);
        }
    }

    return ans;
}

void verify(const vector<int> xs, const int n) {
    assert(xs.size() == n);
    const set<int> xs_set(cbegin(xs), cend(xs));
    assert(xs_set.size() == n);
    assert(*cbegin(xs_set) == 1);
    assert(*crbegin(xs_set) == n);

    int last = -1;
    for (int i = 0; i < n - 1; ++i) {
        assert(xs[i] & xs[i + 1]);
        last = i + 1;
    }

    assert(last == n - 1);
}

void test_it() {
    for (int i = 3; i <= 1000; ++i) {
        if (is_pow2(i)) continue;
        verify(beautiful_permutation(i), i);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // test_it();

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << beautiful_permutation(n) << '\n';
    }

    return 0;
}
