#include <bits/stdc++.h>
using namespace std;

int max_points(const int n, const int m, const int k) {
    const int cards_on_hand = n / k;
    const int winner_jokers = min(m, cards_on_hand);
    const int other_jokers = max(0, m - winner_jokers);
    const int second_jokers = other_jokers % (k - 1) ? (other_jokers / (k - 1) + 1) : (other_jokers / (k - 1));
    return winner_jokers - second_jokers;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        cout << max_points(n, m, k) << '\n';
    }

    return 0;
}
