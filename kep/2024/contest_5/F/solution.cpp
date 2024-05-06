#include "bits/stdc++.h"
using namespace std;

constexpr char chof(const int x) { return (char)(x); }

static constexpr auto A0 = chof(40);
static constexpr auto A1 = chof(41);

static constexpr auto B0 = chof(91);
static constexpr auto B1 = chof(93);

static constexpr auto C0 = chof(123);
static constexpr auto C1 = chof(125);

static constexpr auto D0 = chof(60);
static constexpr auto D1 = chof(62);

bool is_ok(const string &xs) {
    stack<char> st;
    for (const auto x : xs) {
        switch (x) {
        case A0:
        case B0:
        case C0:
        case D0:
            st.push(x);
            break;
        case A1:
            if (empty(st) || st.top() != A0) return false;
            st.pop();
            break;
        case B1:
            if (empty(st) || st.top() != B0) return false;
            st.pop();
            break;
        case C1:
            if (empty(st) || st.top() != C0) return false;
            st.pop();
            break;
        case D1:
            if (empty(st) || st.top() != D0) return false;
            st.pop();
            break;
        default:
            assert(false && "/o\\");
        }
    }
    return empty(st);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    getline(cin, xs);
    if (is_ok(xs)) {
        puts("Yes");
    } else {
        puts("No");
    }
    return 0;
}
