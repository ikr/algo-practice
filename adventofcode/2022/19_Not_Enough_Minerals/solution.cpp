#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

enum class Res { ORE = 0, CLAY = 1, OBSIDIAN = 2, GEODE = 3 };

struct RobotCosts final {
    int ore_ore;
    int clay_ore;
    pii obsidian_ore_clay;
    pii geode_ore_obsidian;
};

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

ostream &operator<<(ostream &os, const RobotCosts &cst) {
    os << '{' << "Ore-R: " << cst.ore_ore << "ore, Clay-R: " << cst.clay_ore
       << "ore, Obsidian-R: " << cst.obsidian_ore_clay.first << "ore "
       << cst.obsidian_ore_clay.second
       << "clay, Geode-R: " << cst.geode_ore_obsidian.first << "ore "
       << cst.geode_ore_obsidian.second << "obsidian}";
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    const regex pattern{
        "^Blueprint [0-9]{1,2}: Each ore robot costs ([0-9]+) ore. Each clay "
        "robot costs ([0-9]+) ore. Each obsidian robot costs ([0-9]+) ore and "
        "([0-9]+) clay. Each geode robot costs ([0-9]+) ore and ([0-9]+) "
        "obsidian.$"};

    vector<RobotCosts> blueprints;

    for (string line; getline(cin, line);) {
        smatch m;
        regex_match(line, m, pattern);
        const auto m_at = [&m](const int i) -> int { return stoi(m[i]); };

        blueprints.push_back(RobotCosts{m_at(1), m_at(2), pii{m_at(3), m_at(4)},
                                        pii{m_at(5), m_at(6)}});

        cerr << blueprints.back() << endl;
    }

    return 0;
}
