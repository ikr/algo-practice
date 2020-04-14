#include <bits/stdc++.h>

using namespace std;

using Coord = complex<int>;

constexpr int row(const Coord &coord) {
    return coord.real();
}

constexpr int col(const Coord &coord) {
    return coord.imag();
}

vector<Coord> block_cells(const Coord &macro_coord) {
    const Coord origin = 3 * macro_coord;
    
    vector<Coord> ans;
    
    for (int r = 0; r != 3; ++r) {
        for (int c = 0; c != 3; ++c) {
            ans.push_back(origin + Coord{r, c});   
        }
    }
    
    return ans;
}

vector<Coord> coords_to_spoil() {
    set<int> rows{0, 1, 2, 3, 5, 6 ,7, 8};
    set<int> cols{0, 1, 2, 3, 5, 6 ,7, 8};
    
    vector<Coord> ans;
    
    for (int br = 0; br != 3; ++br) {
        for (int bc = 0; bc != 3; ++bc) {
            for (const auto coord : block_cells({br, bc})) {
                if (rows.count(row(coord)) && cols.count(col(coord))) {
                    rows.erase(row(coord));
                    cols.erase(col(coord));
                    ans.push_back({row(coord), col(coord)});
                    break;
                }
            }
        }
    }
    
    cout << "rows size is " << rows.size() << ", cols size is " << cols.size() << endl;
    assert(rows.empty() && cols.empty());
    
    return ans;
}

char spoil(const char d) {
    return '1' + (d - '1' + 1) % 9;
}

int main() {
    int t;
    cin >> t;
    
    for (int i = 0; i != t; ++i) {
        vector<string> rows(9, string(9, ' '));
        for (auto &r : rows) cin >> r;
        
        for (const auto coord : coords_to_spoil()) {
            const char d = rows[row(coord)][col(coord)];
            rows[row(coord)][col(coord)] = spoil(d);
        }
        
        for (const auto &r : rows) {
            cout << r << '\n';
        }
    }
    
    cout << endl;

    return 0;
}
