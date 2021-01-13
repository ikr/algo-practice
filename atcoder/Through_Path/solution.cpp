#include <bits/stdc++.h>
using namespace std;
using ll = long long;

enum class Dir { UP, DOWN };

struct Command final {
    Dir dir;
    int edge_index;
    ll increment;
};

vector<ll> execute_commands(const int n) {
    vector<ll> ans(n, 0);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> edges(n - 1);
    for (auto &[a, b] : edges) {
        cin >> a >> b;
        --a;
        --b;
    }

    int q;
    cin >> q;

    vector<Command> commands(q);
    for (auto &[dir, edge_index, increment] : commands) {
        int t;
        cin >> t;
        dir = (t == 1) ? Dir::UP : Dir::DOWN;

        cin >> edge_index;
        --edge_index;

        cin >> increment;
    }

    for (const auto c : execute_commands(n)) cout << c << '\n';
    return 0;
}
