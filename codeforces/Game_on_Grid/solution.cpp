#include <bits/stdc++.h>
using namespace std;

enum class Outcome { A_WINS, B_WINS, DRAW };

string as_string(const Outcome o) {
    switch (o) {
    case Outcome::A_WINS:
        return "Alice";
    case Outcome::B_WINS:
        return "Bob";
    case Outcome::DRAW:
        return "Draw";
    }

    assert(false && "/o\\");
    return "";
}

Outcome simulate(const int n) {
    const int quads = (n / 2) * (n / 2);
    const int a_quads = (quads + 1) / 2;
    const int a_score = 4 * a_quads;
    const int b_score = n * n - a_score;

    if (a_score > b_score) return Outcome::A_WINS;
    if (a_score < b_score) return Outcome::B_WINS;
    return Outcome::DRAW;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << as_string(simulate(n)) << '\n';
    }

    return 0;
}
