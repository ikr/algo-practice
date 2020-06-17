#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

int tables(const string &xs, const int k) {
    if (xs.empty()) return 0;
    const int sz = xs.size();

    vi left_d(sz, xs.front() == '1' ? 0 : INT_MAX);
    for (int i = 1; i < sz; ++i) {
        if (xs[i] == '1') left_d[i] = 0;
        else {
            left_d[i] = left_d[i - 1] == INT_MAX ? INT_MAX : left_d[i - 1] + 1;
        }
    }

    vi right_d(sz, xs.back() == '1' ? 0 : INT_MAX);
    for (int i = sz - 2; i >= 0; --i) {
        if (xs[i] == '1') right_d[i] = 0;
        else {
            right_d[i] = right_d[i + 1] == INT_MAX ? INT_MAX : right_d[i + 1] + 1;
        }
    }

    int ans = 0;
    int last = -1;
    for (int i = 0; i != sz; ++i) {
        if (xs[i] == '0' && left_d[i] > k && right_d[i] > k) {
            if (last == -1 || i - last > k) {
                ++ans;
                last = i;
            }
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int sz, k;
        cin >> sz >> k;
        string xs(sz, ' ');
        cin >> xs;
        cout << tables(xs, k) << '\n';
    }

    return 0;
}
