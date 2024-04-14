#include <bits/stdc++.h>
using namespace std;

bool divides_just_once(const int d, const int x) {
    assert(x % d == 0);
    return (x / d) % d;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int a, b;
    cin >> a >> b;

    int result{};
    for (int x = a; x <= b; ++x) {
        for (const auto d : {2, 3, 4, 6, 7}) {
            bool divs{false};
            if (x % d == 0) {
                divs = true;
                if (!divides_just_once(d, x)) break;
            }
            result += divs;
        }
    }
    cout << result << '\n';
    return 0;
}
