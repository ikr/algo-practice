#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

int count_moves(const string &s) {
    const int sz = s.size();
    vi lr_reps(sz, 1);
    for (int i = 1; i < sz; ++i) {
        if (s[i] == s[i - 1]) lr_reps[i] = lr_reps[i - 1] + 1;
    }

    vi rl_reps(sz, 1);
    for (int i = sz - 2; i >= 0; --i) {
        if (s[i] == s[i + 1]) rl_reps[i] = rl_reps[i + 1] + 1;
    }

    int pivot = -1;
    int best_d = 0;
    for (int i = 1; i < sz;) {
        if (s[i] != s[i - 1]) {
            const int d = min(lr_reps[i - 1], rl_reps[i]);
            if (d > best_d) {
                best_d = d;
                pivot = i;
            }

            i += d + 1;
        } else {
            ++i;
        }
    }

    if (pivot >= 0) {
        return best_d + count_moves(s.substr(0, pivot - best_d) + s.substr(pivot + best_d));
    }

    return 0;
}

bool can_a_win(const string &s) { return count_moves(s) % 2; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << (can_a_win(s) ? "DA" : "NET") << '\n';
    }

    return 0;
}
