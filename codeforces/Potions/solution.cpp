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
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_drinks(const vll &xs) {
    // Max potions drunk — the answer — [from index i] [to index j] inclusive
    vvi potions(sz(xs), vi(sz(xs), 0));

    // Remaining health [from index i] [to index j] inclusive
    vvll health(sz(xs), vll(sz(xs), 0));

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] >= 0) {
            potions[i][i] = 1;
            health[i][i] = xs[i];
        }
    }

    for (int span = 2; span <= sz(xs); ++span) {
        for (int i = 0; i + span <= sz(xs); ++i) {
            const int j = i + span - 1;

            if (health[i][j - 1] + xs[j] >= 0 &&
                potions[i][j - 1] + 1 > potions[i + 1][j]) {
                potions[i][j] = potions[i][j - 1] + 1;
                health[i][j] = health[i][j - 1] + xs[j];
            }

            if (potions[i][j - 1] > potions[i][j]) {
                potions[i][j] = potions[i][j - 1];
                health[i][j] = health[i][j - 1];
            }

            if (potions[i + 1][j] > potions[i][j]) {
                potions[i][j] = potions[i + 1][j];
                health[i][j] = health[i + 1][j];
            }
        }
    }

    cerr << potions << endl;
    cerr << health << endl;

    return potions[0].back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vll xs(n);
    for (auto &x : xs) cin >> x;

    cout << max_drinks(xs) << '\n';
    return 0;
}
