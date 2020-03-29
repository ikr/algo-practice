#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;

    string s(N, 'A');
    iota(s.begin(), s.end(), 'A');

    sort(s.begin(), s.end(), [](const char c1, const char c2) {
        cout << "? " << c1 << ' ' << c2 << endl;

        char res;
        cin >> res;

        return res == '<';
    });

    cout << "! " << s << endl;
}
