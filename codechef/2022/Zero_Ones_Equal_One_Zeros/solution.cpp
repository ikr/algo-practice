#include <iostream>
#include <string>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string sought_s(const int N) {
    if (N % 2) {
        return string((N - 1) / 2, '0') + "1" + string((N - 1) / 2, '0');
    } else {
        const string infix(N - 4, '0');
        return "10" + infix + "01";
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

        cout << sought_s(N) << '\n';
    }

    return 0;
}
