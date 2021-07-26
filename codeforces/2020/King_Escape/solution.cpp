#include <bits/stdc++.h>

using namespace std;

using RowCol = pair<int, int>;
enum class Quadrant { BORDER, NE, SE, SW, NW };

Quadrant quadrant(const RowCol &center, const RowCol &x) {
    if (x.first < center.first && x.second < center.second) return Quadrant::NW;
    if (x.first < center.first && x.second > center.second) return Quadrant::NE;
    if (x.first > center.first && x.second > center.second) return Quadrant::SE;
    if (x.first > center.first && x.second < center.second) return Quadrant::SW;

    return Quadrant::BORDER;
}

bool is_in_check(const RowCol &queen_pos, const RowCol &x) {
    return x.first == queen_pos.first || x.second == queen_pos.second ||
           abs(x.first - queen_pos.first) == abs(x.second - queen_pos.second);
}

bool confirm_king_can_escape(const RowCol &queen_pos, const RowCol &king_pos,
                             const RowCol &exit_pos) {
    if (is_in_check(queen_pos, exit_pos) || is_in_check(queen_pos, king_pos))
        return false;

    return quadrant(queen_pos, king_pos) == quadrant(queen_pos, exit_pos);
}

int main() {
    int sz{0};
    cin >> sz;
    assert(sz > 0);

    RowCol queen_pos;
    cin >> queen_pos.first >> queen_pos.second;

    RowCol king_pos;
    cin >> king_pos.first >> king_pos.second;

    RowCol exit_pos;
    cin >> exit_pos.first >> exit_pos.second;

    const bool result = confirm_king_can_escape(queen_pos, king_pos, exit_pos);
    cout << (result ? "YES" : "NO") << '\n';
}
