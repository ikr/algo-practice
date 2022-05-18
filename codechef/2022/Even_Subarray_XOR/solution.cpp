#include <iostream>
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

constexpr int gray_code(int x) { return (x >> 1) ^ x; }

pair<vector<int>, vector<int>> construct_A_and_B(const int N) {
    vector<int> A;
    A.reserve(N);
    vector<int> B;
    B.reserve(N);

    int x = 2;
    for (int i = 1; i <= N / 2; ++i) {
        A.push_back(gray_code(x++));
        A.push_back(gray_code(x++));

        B.push_back(gray_code(x++));
        B.push_back(gray_code(x++));
    }

    if (sz(A) < N) {
        A.push_back(299'999);
        B.push_back(300'000);
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
