#include <iostream>
using namespace std;

int num_moves(const int N) {
    const int b = (N / 5) * 2;
    const int r = N % 5;

    switch (r) {
    case 0:
        return b;
    case 1:
    case 2:
    case 3:
        return b + 1;
    case 4:
    default:
        return b + 2;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;
        --N;
        cout << num_moves(N) << '\n';
    }

    return 0;
}
