#include <bits/stdc++.h>

using namespace std;

string kth_string(const int n, const int k) {
    int moves = k - 1;
    int i = n - 2;
    int j = n - 1;

    while (moves) {
        if (j - i == 1) {
            --i;
            j = n - 1;
        } else {
            --j;
        }

        --moves;
    }

    string ans(n, 'a');
    ans[i] = 'b';
    ans[j] = 'b';
    return ans;
}

int main() {
    int t;
    cin >> t;

    for (int i = 0; i != t; ++i) {
        int n, k;
        cin >> n >> k;
        cout << kth_string(n, k) << '\n';
    }

    return 0;
}
