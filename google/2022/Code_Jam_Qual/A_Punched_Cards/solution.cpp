#include <iostream>
using namespace std;

void print_card(const int R, const int C) {
    cout << "..+";
    for (int co = 1; co < C; ++co) {
        cout << "-+";
    }
    cout << "\n..|";
    for (int co = 1; co < C; ++co) {
        cout << ".|";
    }
    cout << '\n';

    const auto print_line = [&](const char a, const char b) {
        cout << a;
        for (int co = 0; co < C; ++co) {
            cout << b << a;
        }
        cout << '\n';
    };

    print_line('+', '-');

    for (int ro = 1; ro < R; ++ro) {
        print_line('|', '.');
        print_line('+', '-');
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int R, C;
        cin >> R >> C;
        cout << "Case #" << i << ":\n";
        print_card(R, C);
    }

    return 0;
}
