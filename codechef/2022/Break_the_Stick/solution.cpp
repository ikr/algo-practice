#include <iostream>
using namespace std;

bool is_possible(const int N, const int X) {
    if (X == 1) return true;

    if (N % 2 == 0) {
        return true;
    } else {
        if (X % 2 == 0) return false;
        return true;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N, X;
        cin >> N >> X;

        cout << (is_possible(N, X) ? "YES" : "NO") << '\n';
    }

    return 0;
}
