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

vector<int> bits_of_indices_of_xs_projection_into_ys(const vector<int> &xs,
                                                     const vector<int> &ys) {
    vector<vector<int>> result;

    const auto recur = [&](const auto self, vector<int> &cur, const int i,
                           const int j) -> void {
        if (i >= sz(xs)) {
            assert(sz(cur) == sz(xs));
            result.push_back(cur);
        }

        if (j >= sz(ys)) return;

        const auto it = find(cbegin(ys) + j, cend(ys), xs[i]);
        if (it == cend(ys)) return;

        cur.push_back(inof(distance(cbegin(ys), it)));
        self(self, cur, i + 1, j + 1);
        cur.pop_back();

        self(self, cur, i, j + 1);
    };

    {
        vector<int> cur;
        recur(recur, cur, 0, 0);
    }

    cerr << "result:\n" << result << '\n';

    vector<int> bits;
    for (int ro = 0; ro < sz(result); ++ro) {
        int x{};

        for (int i = 0; i < sz(result); ++i) {
            x |= (1 << result[ro][i]);
        }

        assert(__builtin_popcount(x) == sz(xs));
        bits.push_back(x);
    }
    return bits;
}

bool is_possible(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    const auto Ha = sz(A);
    const auto Wa = sz(A[0]);
    const auto Hb = sz(B);
    const auto Wb = sz(B[0]);
    if (Ha < Hb || Wa < Wb) return false;

    for (int ro = 0; ro < )

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
