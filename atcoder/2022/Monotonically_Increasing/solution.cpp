#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

void next_seq(const int M, vector<int> &xs) {
    const int N = sz(xs);
    for (int i = N - 1, carry = 1; carry > 0 && i >= 0; --i) {
        if (xs[i] < M - (N - 1 - i)) {
            ++xs[i];
            // cerr << "i:" << i << " xs:" << xs << endl;
            carry = 0;

            for (int j = i + 1; j < N; ++j) {
                xs[j] = xs[j - 1] + 1;
            }

            continue;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> xs(N);
    iota(begin(xs), end(xs), 1);

    for (;;) {
        cout << xs << '\n';
        if (xs[0] == M - N + 1) break;
        next_seq(M, xs);
    }

    return 0;
}
