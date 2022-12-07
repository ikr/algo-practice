#include <bits/stdc++.h>
using namespace std;

using Dir = string;

struct File final {
    string name;
    int size;
};

using Dirs = map<string, vector<Dir>>;
using Files = map<string, vector<File>>;
using Path = vector<string>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

string path_key(const Path &p) {
    string result;

    for (const auto &x : p) {
        if (!result.empty()) result += ":";
        result += x;
    }

    return result;
}

pair<vector<Dir>, vector<File>> parse_lisitng(const vector<string> &lines) {
    vector<Dir> ds;
    vector<File> fs;

    for (const auto &line : lines) {
        const auto ab = split(" ", line);

        if (line[0] == 'd') {
            ds.push_back(ab[1]);
        } else {
            fs.push_back(File{ab[1], stoi(ab[0])});
        }
    }

    return {ds, fs};
}

pair<Dirs, Files> read_filesystem(const vector<string> &lines) {
    Dirs dtree;
    Files ftree;
    Path cur;

    bool listing = false;
    vector<string> output;

    for (const auto &line : lines) {
        if (listing) {
            if (line[0] == '$') {
                const auto [ds, fs] = parse_lisitng(output);
                const auto k = path_key(cur);

                dtree[k] = ds;
                ftree[k] = fs;

                listing = false;
                output.clear();
            } else {
                output.push_back(line);
                continue;
            }
        }

        const auto abc = split(" ", line);
        assert(abc[0] == "$");
        const auto cmd = abc[1];

        if (cmd == "ls") {
            listing = true;
            continue;
        }

        assert(cmd == "cd");
        const auto arg = abc[2];

        if (arg == "..") {
            cur.pop_back();
        } else {
            cur.push_back(arg);
        }
    }

    return {dtree, ftree};
}

int main() {
    vector<string> lines;
    for (string line; getline(cin, line);) {
        lines.push_back(line);
    }

    const auto df = read_filesystem(lines);
    return 0;
}
