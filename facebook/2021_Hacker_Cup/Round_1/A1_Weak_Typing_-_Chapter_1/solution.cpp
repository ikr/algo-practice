#include <bits/stdc++.h>
using namespace std;

enum class Hand { L, R };

constexpr Hand change(const Hand h) {
    return (h == Hand::L) ? Hand::R : Hand::L;
}

constexpr bool covers(const Hand h, const char x) {
    return (x == 'F') || (h == Hand::L && x == 'X') ||
           (h == Hand::R && x == 'O');
}

int hand_switches_num(const string &xs, const Hand start_h) {
    auto h = start_h;
    int ans = 0;

    for (const auto x : xs) {
        if (!covers(h, x)) {
            ++ans;
            h = change(h);
        }
    }

    return ans;
}

int hand_switches_num(const string &xs) {
    return min(hand_switches_num(xs, Hand::L), hand_switches_num(xs, Hand::R));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;

    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;

        string xs(n, ' ');
        cin >> xs;

        cout << "Case #" << i << ": " << hand_switches_num(xs) << '\n';
    }

    return 0;
}
