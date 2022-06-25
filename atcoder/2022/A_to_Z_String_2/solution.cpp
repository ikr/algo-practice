#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

constexpr char chof(const int x) { return static_cast<char>(x); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X;
    cin >> N >> X;
    --X;

    const auto r = X / N;
    cout << chof(inof('A') + r) << '\n';
    return 0;
}
