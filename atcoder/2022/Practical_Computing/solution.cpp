#include <iostream>
#include <vector>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> tri_grid(const int N) {
    vector<vector<int>> grid;

    for (int ro = 0; ro < N; ++ro) {
        vector<int> row(ro + 1, 0);

        for (int co = 0; co <= ro; ++co) {
            if (co == 0 || co == ro) {
                row[co] = 1;
            } else {
                row[co] = grid.back()[co - 1] + grid.back()[co];
            }
        }

        grid.push_back(row);
    }

    return grid;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    cout << tri_grid(N);
    return 0;
}
