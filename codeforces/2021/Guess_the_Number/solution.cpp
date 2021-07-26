#include <bits/stdc++.h>
using namespace std;

enum class Rel { GTE, LT };

Rel rel_to(const int x) {
    cout << x << endl;
    string s;
    cin >> s;

    if (s == "<") return Rel::LT;
    return Rel::GTE;
}

void print_answer(const int x) { cout << "! " << x << endl; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int lo = 1;
    int hi = 1e6;

    if (rel_to(hi) == Rel::GTE) {
        print_answer(hi);
        return 0;
    }

    while (hi - lo > 1) {
        const int mid = lo + (hi - lo) / 2;
        if (rel_to(mid) == Rel::LT) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    print_answer(lo);
    return 0;
}
