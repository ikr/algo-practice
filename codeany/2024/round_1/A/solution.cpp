#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int a, b;
    cin >> a >> b;

    int result{};
    for (int x = a; x <= b; ++x) {
        for (const auto d : {2, 3, 4, 6, 7}) {
            if (x % d == 0) {
                ++result;
                break;
            }
        }
    }
    cout << result << '\n';
    return 0;
}
