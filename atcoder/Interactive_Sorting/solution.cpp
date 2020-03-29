#include <bits/stdc++.h>

using namespace std;

int main() {
    const auto cmp = [](const char c1, const char c2) {
        cout << "? " << c1 << ' ' << c2 << endl;

        char res;
        cin >> res;

        return res == '<';
    };

    const auto head_triple_insert = [cmp](string &y, const char c) {
        if (cmp(c, y[1])) {
            if (cmp(c, y[0]))
                y.insert(0, 1, c);
            else
                y.insert(1, 1, c);
        } else {
            if (cmp(c, y[2]))
                y.insert(2, 1, c);
            else
                y.insert(3, 1, c);
        }
    };

    int N, Q;
    cin >> N >> Q;

    string s(N, 'A');
    iota(s.begin(), s.end(), 'A');

    if (N == 5) {
        if (cmp(s[1], s[0])) swap(s[0], s[1]);
        if (cmp(s[3], s[2])) swap(s[2], s[3]);

        if (cmp(s[3], s[1])) {
            swap(s[0], s[2]);
            swap(s[1], s[3]);
        }

        string y{s[0], s[1], s[3]};
        const char e = s[4];
        const char c = s[2];
        head_triple_insert(y, e);
        head_triple_insert(y, c);

        s = y;
    } else {
        stable_sort(s.begin(), s.end(), cmp);
    }

    cout << "! " << s << endl;
}
