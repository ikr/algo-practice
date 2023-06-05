#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<char, int>> run_length_encoding(const string &xs) {
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

string last_one(const string &xs) {
    const auto rle = run_length_encoding(xs);
    const auto it_hi =
        max_element(cbegin(rle), cend(rle), [](const auto a, const auto b) {
            return a.second < b.second;
        });
    const auto hi = it_hi->second;

    string result;
    for (const auto &[c, f] : rle) {
        if (f == hi) result += c;
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << last_one(xs) << '\n';
    }

    return 0;
}
