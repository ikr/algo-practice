#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string play(vector<int> xs) {
    sort(rbegin(xs), rend(xs));

    deque<int> even;
    deque<int> odd;
    for (const int x : xs) {
        if (x % 2) {
            odd.push_back(x);
        } else {
            even.push_back(x);
        }
    }

    ll score_a = 0;
    ll score_b = 0;
    bool a_turn = true;

    while (!even.empty() || !odd.empty()) {
        if (a_turn) {
            if (!even.empty() && !odd.empty()) {
                if (odd.front() > even.front()) {
                    odd.pop_front();
                } else {
                    score_a += even.front();
                    even.pop_front();
                }
            } else if (!even.empty()) {
                score_a += even.front();
                even.pop_front();
            } else {
                odd.pop_front();
            }
        } else {
            if (!even.empty() && !odd.empty()) {
                if (even.front() > odd.front()) {
                    even.pop_front();
                } else {
                    score_b += odd.front();
                    odd.pop_front();
                }
            } else if (!odd.empty()) {
                score_b += odd.front();
                odd.pop_front();
            } else {
                even.pop_front();
            }
        }

        a_turn = !a_turn;
    }

    if (score_a == score_b) return "Tie";
    return score_a > score_b ? "Alice" : "Bob";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> xs(n);
        for (auto &x : xs) cin >> x;
        cout << play(move(xs)) << '\n';
    }

    return 0;
}
