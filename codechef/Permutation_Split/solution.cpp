#include <bits/stdc++.h>
using namespace std;

int inversions(const vector<int> &xs) {
    const int n = xs.size();
    int ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (xs[i] > xs[j]) ++ans;
        }
    }
    return ans;
}

vector<int> subseq(const unsigned int mask, const vector<int> &xs) {
    bitset<16> bits{mask};
    vector<int> ans;
    const int n = xs.size();

    for (int i = 0; i < n; ++i) {
        if (bits.test(i)) ans.push_back(xs[i]);
    }

    return ans;
}

bool can_split(const vector<int> &xs) {
    const int n = xs.size();
    for (int i = 0; i <= (1 << n) - 1; ++i) {
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;
        cout << (can_split(xs) ? "YES\n" : "NO\n");
    }

    return 0;
}
