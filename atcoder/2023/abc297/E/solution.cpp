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

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll kth_lowest(const vector<ll> &A, const int K) {
    vector<int> xs{0};
    int i0{};

    const auto next_addition = [&]() -> pii {
        for (int i = i0; i < sz(xs); ++i) {
            for (const auto a : A) {
                if (xs[i] + a > xs.back()) {
                    return {xs[i] + a, i};
                }
            }
        }

        assert(false && "/o\\");
        return {};
    };

    while (sz(xs) <= K) {
        const auto [x, i] = next_addition();
        xs.push_back(x);
        i0 = i;
    }

    cerr << xs << endl;
    return xs[K];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, K;
    cin >> N >> K;

    vector<ll> A(N);
    for (auto &a : A) cin >> a;
    sort(begin(A), end(A));
    A.erase(unique(begin(A), end(A)), end(A));

    cout << kth_lowest(A, K) << '\n';
    return 0;
}
