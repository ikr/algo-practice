#include <bits/stdc++.h>
using namespace std;

static const string Lo{"sovuq"};
static const string Ok{"yaxshi"};
static const string Hi{"issiq"};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    const string ans = (n < 20 ? Lo : (30 < n ? Hi : Ok));
    cout << ans << '\n';
    return 0;
}
