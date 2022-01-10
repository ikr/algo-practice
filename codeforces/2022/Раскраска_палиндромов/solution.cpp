#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

priority_queue<int> gather_freqs(const string &xs) {
    map<char, int> fs;
    for (const auto x : xs) ++fs[x];

    priority_queue<int> ans;
    for (const auto [_, f] : fs) {
        ans.push(f);
    }
    return ans;
}

int max_length_of_shortest_palindrome(const int k, const string &xs) {
    auto fs = gather_freqs(xs);

    priority_queue<int, vector<int>, greater<int>> g;
    for (int i = 1; i <= k; ++i) {
        g.push(0);
    }

    while (!fs.empty() && fs.top() > 1) {
        const auto l = g.top();
        g.pop();

        const auto f = fs.top();
        assert(f >= 2);
        fs.pop();

        g.push(l + 2);
        if (f - 2 > 0) fs.push(f - 2);
    }

    assert(fs.empty() || fs.top() == 1);

    auto ones = sz(fs);
    while (g.top() % 2 == 0 && ones > 0) {
        const auto l = g.top();
        g.pop();

        g.push(l + 1);
        --ones;
    }

    return g.top();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        string xs(n, ' ');
        cin >> xs;

        cout << max_length_of_shortest_palindrome(k, xs) << '\n';
    }

    return 0;
}
