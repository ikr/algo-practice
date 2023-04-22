#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;

    int lo = 1;
    int hi = N;

    while (lo + 1 < hi) {
        const auto mid = lo + (hi - lo) / 2;
        cout << "? " << mid << endl;

        int s;
        cin >> s;

        if (s == 0) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    cout << "! " << lo << endl;
    return 0;
}
