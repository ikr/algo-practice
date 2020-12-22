#include <bits/stdc++.h>
using namespace std;

struct Tile final {
    Tile(const int id, const vector<string> &rows) : m_id{id}, m_rows{rows} {}
    Tile() : m_id{0}, m_rows{} {}

  private:
    int m_id;
    vector<string> m_rows;
};

int main() {
    vector<Tile> tiles;
    int id = 0;
    vector<string> rows;

    for (string line; getline(cin, line);) {
        const string header{"Tile "};
        if (line.find(header) == 0) {
            id = stoi(line.substr(header.size(), 4));
            continue;
        }

        if (line == "") {
            tiles.emplace_back(id, rows);
            id = 0;
            rows.clear();
            continue;
        }

        rows.push_back(line);
    }
    return 0;
}
