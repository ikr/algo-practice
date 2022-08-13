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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> transpose(const vector<vector<int>> &grid) {
    vector<vector<int>> result(sz(grid[0]), vector(sz(grid), 0));

    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[0]); ++co) {
            result[co][ro] = grid[ro][co];
        }
    }

    return result;
}

void remove_row(vector<vector<int>> &grid, const int ro) {
    assert(ro < sz(grid));
    grid.erase(cbegin(grid) + ro);
}

vector<vector<int>> num_indices(const int n, const int k) {
    assert(n <= 10);
    assert(k < n);

    if (k == 0) return {vector<int>{}};

    vector<vector<int>> result;

    for (int bits = 1; bits < (1 << n); ++bits) {
        if (__builtin_popcount(bits) != k) continue;

        vector<int> x;
        for (int i = 0; i < n; ++i) {
            if (bits & (1 << i)) x.push_back(i);
        }
        assert(sz(x) == k);
        result.push_back(x);
    }

    return result;
}

bool is_possible(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    const auto Ha = sz(A);
    const auto Wa = sz(A[0]);
    const auto Hb = sz(B);
    const auto Wb = sz(B[0]);
    if (Ha < Hb || Wa < Wb) return false;
    if (Ha == Hb && Wa == Wb) return A == B;

    for (const auto &iro : num_indices(Ha, Ha - Hb)) {
        for (const auto &ico : num_indices(Wa, Wa - Wb)) {
            auto grid = A;
            for (auto it = crbegin(iro); it != crend(iro); ++it) {
                remove_row(grid, *it);
            }

            grid = transpose(grid);
            for (auto it = crbegin(ico); it != crend(ico); ++it) {
                remove_row(grid, *it);
            }
            grid = transpose(grid);

            if (grid == B) return true;
        }
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int ha, wa;
    cin >> ha >> wa;

    vector<vector<int>> A(ha, vector<int>(wa));
    for (auto &row : A) {
        for (auto &a : row) {
            cin >> a;
        }
    }

    int hb, wb;
    cin >> hb >> wb;

    vector<vector<int>> B(hb, vector<int>(wb));
    for (auto &row : B) {
        for (auto &b : row) {
            cin >> b;
        }
    }

    cout << (is_possible(A, B) ? "Yes" : "No") << '\n';
    return 0;
}
