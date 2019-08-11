#include <bits/stdc++.h>

using namespace std;

bool can_win(const vector<int> &row, const int m, const int k) {
    int bag = m;

    for (unsigned int i = 0; i < row.size() - 1; ++i) {
        const int h0 = row[i];
        const int h1 = row[i + 1];

        const int delta = abs(h1 - h0);

        if (h0 <= h1) {
            const int extra = delta - k;

            if (extra > 0)
                if (bag >= extra)
                    bag -= extra;
                else
                    return false;
            else
                bag += min(-extra, h0);
        } else {
            bag += min(delta + k, h0);
        }
    }

    return true;
}

int main() {
    int test_cases_count;
    cin >> test_cases_count;

    for (int i = 0; i != test_cases_count; ++i) {
        int n;
        int m;
        int k;
        cin >> n >> m >> k;

        vector<int> row(n);
        for (auto &c : row) {
            cin >> c;
        }

        cout << (can_win(row, m, k) ? "YES" : "NO") << '\n';
    }
}
