#include <atcoder/fenwicktree>
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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int N_MAX = 3 * 100'000;

int max_target(const vector<int> &A, const vector<int> &B) {
    const auto N = sz(A);
    atcoder::fenwick_tree<int> fa(N_MAX + 1);
    atcoder::fenwick_tree<int> fb(N_MAX + 1);

    vector<int> inv_a(N, 0);
    vector<int> inv_b(N, 0);

    for (int i = N - 1; i >= 0; --i) {
        inv_a[i] = fa.sum(0, A[i]);
        inv_b[i] = fb.sum(0, B[i]);

        fa.add(A[i], 1);
        fb.add(B[i], 1);
    }

    int lis_a{}, lis_b{};

    for (int i = N - 1; i >= 0; --i) {
        const auto tail = N - 1 - i;

        if (inv_a[i] == 0 && inv_b[i] == 0) {
            ++lis_a;
            ++lis_b;
            continue;
        }

        if (inv_a[i] == tail && inv_b[i] == tail) {
            ++lis_a;
            ++lis_b;
            continue;
        }

        if (inv_a[i] == 0) {
            ++lis_a;
            continue;
        }

        if (inv_b[i] == 0) {
            ++lis_b;
            continue;
        }

        if (inv_a[i] == tail) {
            ++lis_a;
            continue;
        }

        if (inv_b[i] == tail) {
            ++lis_b;
            continue;
        }
    }

    // cerr << "inv_a: " << inv_a << " inv_b: " << inv_b << endl;

    return lis_a + lis_b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    vector<int> B(N);
    for (auto &b : B) cin >> b;

    cout << max_target(A, B) << '\n';
    return 0;
}
