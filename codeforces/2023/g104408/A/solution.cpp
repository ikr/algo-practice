#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;

string last_one(const string &xs) {
    array<int, AZ> freq{};
    for (const auto x : xs) {
        ++freq[inof(x) - inof('a')];
    }

    const auto hi = *max_element(cbegin(freq), cend(freq));
    array<bool, AZ> need{};
    for (int i = 0; i < AZ; ++i) {
        if (freq[i] == hi) need[i] = true;
    }

    string result;
    for (int i = sz(xs) - 1; i >= 0; --i) {
        const auto code = inof(xs[i]) - inof('a');
        if (need[code]) {
            result += xs[i];
            need[code] = false;
        }
    }
    reverse(begin(result), end(result));
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
