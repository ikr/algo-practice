#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<char, int>> encode(const string &xs) {
    vector<pair<char, int>> result{{xs[0], 1}};

    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == result.back().first) {
            ++(result.back().second);
        } else {
            result.emplace_back(xs[i], 1);
        }
    }

    return result;
}

bool is_possible(const string &S, const string &T) {
    const auto xs = encode(S);
    const auto ys = encode(T);

    int i = 0, j = 0;
    for (; i < sz(xs) && j < sz(ys); ++i, ++j) {
        if (xs[i].first != ys[j].first || xs[i].second > ys[j].second) {
            return false;
        }
        if (xs[i].second == ys[j].second) continue;
        if (xs[i].second == 1) return false;
    }

    return i == sz(xs) && j == sz(ys);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string S, T;
    cin >> S >> T;

    cout << (is_possible(S, T) ? "Yes" : "No") << '\n';
    return 0;
}
