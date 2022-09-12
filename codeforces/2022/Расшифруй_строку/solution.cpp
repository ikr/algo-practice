#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char chof(const int x) { return static_cast<char>(x); }

char decode_term(const string &x) {
    const auto index = stoi(x) - 1;
    return chof(inof('a') + index);
}

string decode(const string &xs) {
    string result;

    for (int i = sz(xs) - 1; i >= 0;) {
        if (xs[i] == '0') {
            result += decode_term(string{xs[i - 2], xs[i - 1]});
            i -= 3;

        } else {
            result += decode_term(string{xs[i]});
            --i;
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
        int n;
        cin >> n;

        string xs;
        cin >> xs;

        assert(sz(xs) == n);
        cout << decode(xs) << '\n';
    }

    return 0;
}
