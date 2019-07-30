#include <bits/stdc++.h>

using namespace std;

int main() {
    long long H;
    long long L;
    cin >> H >> L;

    const long double X =
        static_cast<long double>(L * L) / (2.0L * H) - H / 2.0L;

    cout.precision(17);
    cout << X << '\n';
}
