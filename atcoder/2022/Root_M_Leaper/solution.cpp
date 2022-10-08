#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
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

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

vector<pii> joining_squares(const int N, const int M) {
    vector<pii> result;

    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            if (i * i + j * j == M) {
                result.emplace_back(i, j);
            }
        }
    }

    return result;
}

vector<vector<int>> moves_matrix(const int N, const int M) {
    const auto jsq = joining_squares(N, M);

    const auto in_bounds_scalar = [&](const int x) -> bool {
        return 0 <= x && x < N;
    };

    const auto in_bounds = [&](const pii roco) -> bool {
        return in_bounds_scalar(roco.first) && in_bounds_scalar(roco.second);
    };

    const auto adjacent = [&](const pii roco) -> set<pii> {
        set<pii> result;
        for (const auto &[a, b] : jsq) {
            const vector<pii> ds{{-a, -b}, {a, -b}, {a, b}, {-a, b},
                                 {-b, -a}, {b, -a}, {b, a}, {-b, a}};
            for (const auto &delta : ds) {
                const auto u = roco + delta;
                if (in_bounds(u)) {
                    result.insert(u);
                }
            }
        }
        return result;
    };

    vector<vector<int>> result(N, vector(N, -1));
    result[0][0] = 0;
    queue<pii> q;
    q.emplace(0, 0);

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        const auto [ro0, co0] = u;

        for (const auto &v : adjacent(u)) {
            const auto [ro, co] = v;
            if (result[ro][co] >= 0) continue;

            result[ro][co] = result[ro0][co0] + 1;
            q.emplace(ro, co);
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    cout << moves_matrix(N, M);
    return 0;
}
