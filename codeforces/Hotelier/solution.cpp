#include <bits/stdc++.h>

using namespace std;

int main() {
    unsigned int n;
    cin >> n;

    string events;
    cin >> events;
    assert(events.size() == n);

    vector<bool> rooms(10);
    for (const auto ev : events) {
        if ('0' <= ev && ev <= '9') {
            rooms[ev - '0'] = false;
        } else if (ev == 'L') {
            auto it = find(begin(rooms), end(rooms), false);
            *it = true;
        } else if (ev == 'R') {
            auto it = find(rbegin(rooms), rend(rooms), false);
            *it = true;
        }
    }

    for (const auto r : rooms) {
        cout << r;
    }

    cout << '\n';
}
