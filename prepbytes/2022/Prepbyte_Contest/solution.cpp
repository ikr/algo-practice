#include <bits/stdc++.h>
using namespace std;

const string AL{"Alice"};
const string BO{"Bob"};

string winner(int A, int B) {
    for (int i = 1;; ++i) {
        if (i % 2) { // Alice's move
            if (A < i) return BO;
            A -= i;
        } else { // Bob's move
            if (B < i) return AL;
            B -= i;
        }
    }

    assert(false && "/o\\");
    return "";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int A, B;
        cin >> A >> B;

        cout << winner(A, B) << '\n';
    }

    return 0;
}
