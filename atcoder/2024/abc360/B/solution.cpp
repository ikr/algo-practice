#include <bits/stdc++.h>
using namespace std;

ostream &operator<<(ostream &os, const vector<string> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> chunks(const string &xs, const int k) {
    assert(k < sz(xs));
    vector<string> result;
    for (int i = 0; i < sz(xs); i += k) {
        result.push_back(xs.substr(i, k));
    }
    return result;
}

string column(const vector<string> &grid, const int co) {
    string result;
    for (const auto &row : grid) {
        if (co < sz(row)) {
            result += row[co];
        }
    }
    return result;
}

bool can_match(const string &s, const string &t) {
    for (int k = 1; k < sz(s) - 1; ++k) {
        const auto grid = chunks(s, k);
        for (int j = 0; j < k; ++j) {
            if (column(grid, j) == t) return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    cin >> s;

    string t;
    cin >> t;

    cout << (can_match(s, t) ? "Yes" : "No") << '\n';
    return 0;
}
