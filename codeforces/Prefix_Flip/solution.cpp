#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

constexpr char flip(const char b) { return b == '1' ? '0' : '1'; }

vector<int> seq_to_zero(string bits) {
    const int sz = bits.size();
    vector<int> ans;

    for (int i = 0; i < sz - 1; ++i) {
        if (bits[i] != bits[i + 1]) {
            ans.push_back(i + 1);
            transform(bits.cbegin(), bits.cbegin() + i + 1, bits.begin(), flip);
        }
    }

    if (all_of(bits.cbegin(), bits.cend(),
               [](const char b) { return b == '1'; })) {
        ans.push_back(sz);
    }

    return ans;
}

vector<int> prefix_lengths_sequence(const string &a, const string &b) {
    if (a == b) return {};

    auto b_seq = seq_to_zero(b);
    reverse(b_seq.begin(), b_seq.end());

    auto a_seq = seq_to_zero(a);
    a_seq.insert(a_seq.cend(), b_seq.cbegin(), b_seq.cend());
    return a_seq;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int sz;
        cin >> sz;

        string a(sz, ' ');
        string b(sz, ' ');
        cin >> a >> b;

        const auto ans = prefix_lengths_sequence(a, b);
        cout << ans.size();
        for (const auto l : ans) {
            cout << ' ' << l;
        }
        cout << '\n';
    }

    return 0;
}
