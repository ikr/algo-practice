#include <bits/stdc++.h>
using namespace std;

multiset<int> gather_span_lengths(const vector<bool> &xs) {
    const int n = xs.size();

    int start = -1;
    multiset<int> ans;

    for (int i = 0; i < n; ++i) {
        if (xs[i]) {
            if (start == -1) continue;
            ans.insert(i - start);
            start = -1;
        } else {
            if (start != -1) continue;
            start = i;
        }
    }

    return ans;
}

bool winning(const multiset<int> &spans) {
    if (spans.empty()) return false;

    const int hi = *crbegin(spans);
    if (hi % 2 == 0) return false;

    if (spans.size() == 1U) return true;

    auto it = crbegin(spans);
    ++it;

    const int sub = *it;
    return sub <= (hi - 1) / 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<bool> xs(n, false);
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            xs[i] = x == 1;
        }

        cout << (winning(gather_span_lengths(xs)) ? "Yes" : "No") << '\n';
    }

    return 0;
}
