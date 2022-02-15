#include <cctype>
#include <iostream>
#include <set>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

enum class Owner { Alice, Bob, Nobody };

static const set<char> VOWELS{'A', 'E', 'I', 'O', 'U'};

Owner classify(const string &name) {
    const auto last = toupper(name.back(), locale::classic());
    if (last == 'Y') return Owner::Nobody;
    return VOWELS.count(last) ? Owner::Alice : Owner::Bob;
}

string owner_literal(const Owner x) {
    switch (x) {
    case Owner::Alice:
        return "Alice";
    case Owner::Bob:
        return "Bob";
    case Owner::Nobody:
    default:
        return "nobody";
    }
}

string solve(const string &name) {
    return name + " is ruled by " + owner_literal(classify(name)) + ".";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        string name;
        cin >> name;

        cout << "Case #" << i << ": " << solve(name) << '\n';
    }

    return 0;
}
