#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi gather_freqs(const string &xs) {
    map<char, int> fs;
    for (const auto x : xs) ++fs[x];

    vi ans;
    for (const auto [_, f] : fs) {
        ans.push_back(f);
    }
    return ans;
}

int max_length_of_shortest_palindrome(const int k, const string &xs) {
    const auto fs = gather_freqs(xs);
    const auto pairs_num =
        transform_reduce(cbegin(fs), cend(fs), 0, plus<int>{},
                         [](const auto f) { return f / 2; });
    const auto total_num = accumulate(cbegin(fs), cend(fs), 0);
    const auto final_drop = total_num - (pairs_num / k) * k * 2 >= k ? 1 : 0;
    return (pairs_num / k) * 2 + final_drop;
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
