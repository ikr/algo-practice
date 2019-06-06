#include <bits/stdc++.h>

using namespace std;

int main() {
    int people_count;
    cin >> people_count;

    bool is_hard_overall{false};

    for (int i = 0; i != people_count; ++i) {
        bool is_hard_for_the_person;
        cin >> is_hard_for_the_person;
        if (is_hard_for_the_person) is_hard_overall = true;
    }

    cout << (is_hard_overall ? "HARD" : "EASY") << endl;
}
