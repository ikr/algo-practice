#include <bits/stdc++.h>
using namespace std;

vector<string> gray_seq(const int n) {
    if (n == 0) return {""};

    auto aa = gray_seq(n - 1);
    auto bb = aa;
    reverse(begin(bb), end(bb));

    for (auto &a : aa) a.insert(0, 1, '0');
    for (auto &b : bb) b.insert(0, 1, '1');

    aa.insert(aa.end(), make_move_iterator(bb.begin()),
              make_move_iterator(bb.end()));
    return aa;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (const auto &b : gray_seq(n)) cout << b << '\n';
    return 0;
}
