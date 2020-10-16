#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr int SZ = 'z' - 'a' + 1;

namespace atcoder {
template <class T> struct fenwick_tree final {
    fenwick_tree() : _n(0) {}
    fenwick_tree(int n) : _n(n), data(n) {}

    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p - 1] += x;
            p += p & -p;
        }
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

  private:
    int _n;
    vector<T> data;

    T sum(int r) {
        T s = 0;
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
    atcoder::fenwick_tree<int> t(n);

    for (int i = n - 1; i >= 0; --i) {
        t.add(xs[i], 1);
        ans += t.sum(0, xs[i]);
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
