#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr char chof(const T x) {
    return static_cast<char>(x);
}
template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string translate(const string &alpha, const string &s) {
    string ans = s;
    for (auto &x : ans) {
        const int i = inof(alpha.find(x));
        x = chof(inof('a') + i);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string X;
    cin >> X;

    int N;
    cin >> N;

    vector<string> xs(N);
    for (int i = 0; i < N; ++i) {
        cin >> xs[i];
    }

    vi idx(N, 0);
    iota(begin(idx), end(idx), 0);

    sort(begin(idx), end(idx), [&](const int x, const int y) {
        const auto a = translate(X, xs[x]);
        const auto b = translate(X, xs[y]);
        return lexicographical_compare(cbegin(a), cend(a), cbegin(b), cend(b));
    });

    for (const int i : idx) {
        cout << xs[i] << '\n';
    }

    return 0;
}
