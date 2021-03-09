#include <bits/stdc++.h>
using namespace std;

struct Instr final {
    int op;
    int x;
    int y;
};

constexpr Instr read_insrt(const int code) {
    return {code / 100, (code % 100) / 10, code % 10};
}

int main() {
    for (string line; getline(cin, line);) {
    }
    return 0;
}
