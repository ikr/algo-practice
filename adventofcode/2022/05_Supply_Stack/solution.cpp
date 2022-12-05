#include <bits/stdc++.h>
using namespace std;

static constexpr int NUM_STACKS = 9;

struct Command final {
    int num;
    int src;
    int dst;
};

array<string, NUM_STACKS> read_stacks() {
    array<string, NUM_STACKS> result;
    result.fill("");

    for (string line; getline(cin, line);) {
        if (line == "") break;
        if (line[1] == '1') continue;

        for (int i = 0; i < NUM_STACKS; ++i) {
            const auto x = line[1 + i * 4];
            if (x != ' ') result[i].push_back(x);
        }
    }

    return result;
}

vector<Command> read_commands() {
    const regex pattern{"^move ([0-9]+) from ([1-9]+) to ([1-9]+)$"};
    vector<Command> result;

    for (string line; getline(cin, line);) {
        smatch m;
        regex_match(line, m, pattern);
        result.push_back(Command{stoi(m[1].str()), stoi(m[2].str()) - 1,
                                 stoi(m[3].str()) - 1});
    }

    return result;
}

void exec_command(array<string, NUM_STACKS> &st, const Command &cmd) {
    auto x = st[cmd.src].substr(0, cmd.num);
    reverse(begin(x), end(x));

    st[cmd.src] = st[cmd.src].substr(cmd.num);
    st[cmd.dst].insert(cbegin(st[cmd.dst]), cbegin(x), cend(x));
}

int main() {
    auto st = read_stacks();
    const auto commands = read_commands();
    for (const auto &cmd : commands) exec_command(st, cmd);

    string result(NUM_STACKS, ' ');
    transform(cbegin(st), cend(st), begin(result),
              [](const auto &x) { return x.empty() ? ' ' : x[0]; });
    cout << result << '\n';
    return 0;
}
