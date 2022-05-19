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

pair<vector<int>, vector<int>> construct_A_and_B(const int N) {
    vector<int> A;
    A.reserve(N);
    vector<int> B;
    B.reserve(N);

    for (int i = 1; i <= N; ++i) {
        A.push_back(2 * i);
        B.push_back(2 * i + 1);
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
