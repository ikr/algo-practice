#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
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

vector<int> recover_A(const vector<int> &B) {
    const auto xor_b =
        accumulate(cbegin(B), cend(B), 0,
                   [](const int agg, const int b) { return agg ^ b; });

    const auto all_a = xor_b ^ xor_b ^ xor_b;

    vector<int> A;
    A.reserve(sz(B) - 1);
    int num_zeros{};

    for (const auto b : B) {
        const auto s = b ^ all_a;

        if (!s) {
            ++num_zeros;
        } else {
            A.push_back(s);
        }
    }

    for (int i = 2; i <= num_zeros; ++i) {
        A.push_back(0);
    }

    sort(begin(A), end(A));
    return A;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        vector<int> B(N + 1);
        for (auto &b : B) cin >> b;

        cout << recover_A(B) << '\n';
    }

    return 0;
}
