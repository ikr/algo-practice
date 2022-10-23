#include <bits/stdc++.h>
using namespace std;

string a_proper_word(const int N) {
    assert((N - 7) % 4 == 0);
    const auto pairs_to_add = (N - 7) / 4;

    string pre;
    for (int i = 1; i <= pairs_to_add; ++i) {
        pre += "ad";
    }

    auto suf = pre;
    reverse(begin(suf), end(suf));

    return pre + "wadidaw" + suf;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    cout << a_proper_word(N) << '\n';
    return 0;
}
