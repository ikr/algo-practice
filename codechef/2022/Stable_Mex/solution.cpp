#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int mex_of(const vector<int> &A) {
    if (A[0] != 0) return 0;

    for (int i = 1; i < sz(A); ++i) {
        if (A[i - 1] + 1 != A[i]) return A[i - 1] + 1;
    }

    return A.back() + 1;
}

vector<int> span_lengths(const vector<int>::const_iterator &first,
                         const vector<int>::const_iterator &last) {
    vector<int> result;

    for (auto it = first; it != last;) {
        auto jt = next(it);
        while (jt != last && (*it) + 1 == *jt) ++jt;
        result.push_back(inof(distance(it, jt)));
        it = jt;
    }

    return result;
}

int ks_num(const vector<int> &A) {
    if (A[0] > 1) return A[0] - 1;

    const auto m = mex_of(A);
    if (m == 0) return 0;
    if (m == 1) return -1;

    const auto ls =
        span_lengths(next(lower_bound(cbegin(A), cend(A), m)), cend(A));

    return inof(count_if(cbegin(ls), cend(ls),
                         [m](const int l) { return l >= m - 1; }));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        vector<int> A(N);
        for (auto &a : A) cin >> a;

        sort(begin(A), end(A));
        A.erase(unique(begin(A), end(A)), end(A));

        cout << ks_num(A) << '\n';
    }

    return 0;
}
