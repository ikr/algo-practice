#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

enum class Outcome { IMPOSSIBLE, BLUE_WINS, RED_WINS, NEUTRAL };

string outcome_literal(const Outcome x) {
    switch (x) {
    case Outcome::IMPOSSIBLE:
        return "Impossible";
    case Outcome::BLUE_WINS:
        return "Blue wins";
    case Outcome::RED_WINS:
        return "Red wins";
    case Outcome::NEUTRAL:
    default:
        return "Nobody wins";
    }
}

Outcome solve(const vector<string> &grid) { return Outcome::NEUTRAL; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<string> grid(N);
        for (auto &row : grid) {
            cin >> row;
        }

        cout << "Case #" << i << ": " << outcome_literal(solve(grid)) << '\n';
    }

    return 0;
}
