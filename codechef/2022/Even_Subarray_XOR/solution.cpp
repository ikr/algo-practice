#include <iostream>
#include <queue>
#include <utility>
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

static constexpr int X_MAX = 300'000;

constexpr int gray_code(int x) { return (x >> 1) ^ x; }

pair<vector<int>, vector<int>> construct_A_and_B(const int N) {
    vector<int> A;
    A.reserve(N);
    vector<int> B;
    B.reserve(N);

    vector<int> res{1, X_MAX - 1, X_MAX};
    const auto gray_code_plus = [&](const int x) -> int {
        const auto y = gray_code(x);
        if (y < X_MAX) return y;

        const auto z = res.back();
        res.pop_back();
        return z;
    };

    int x = 2;
    for (int i = 1; i <= N / 2; ++i) {
        A.push_back(gray_code_plus(x++));
        A.push_back(gray_code_plus(x++));

        B.push_back(gray_code_plus(x++));
        B.push_back(gray_code_plus(x++));
    }

    if (sz(A) < N) {
        A.push_back(gray_code_plus(x++));
        B.push_back(gray_code_plus(x++));
    }

    return {A, B};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        const auto [A, B] = construct_A_and_B(N);
        cout << A << '\n' << B << '\n';
    }

    return 0;
}
