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

vector<int> positions_of_ones(const int N, const vector<int> &A) {
    const auto M = sz(A);
    vector<int> xs(N);
    iota(begin(xs), end(xs), 1);

    for (int i = 0; i < M - 1; ++i) {
        swap(xs[A[i]], xs[A[i] + 1]);
    }

    cerr << xs << endl;

    vector<int> D(M, 1);
    return D;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> A(M);
    for (auto &a : A) {
        cin >> a;
        --a;
    }

    for (const auto i : positions_of_ones(N, A)) {
        cout << i << '\n';
    }
    return 0;
}
