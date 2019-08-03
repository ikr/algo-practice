#include <bits/stdc++.h>
#include <variant>

using namespace std;

using ui_t = unsigned int;
enum class EventType { RECEIPT = 1, PAYOFF = 2 };

struct Receipt {
    ui_t pereson;
    ui_t balance;
};

struct Payoff {
    ui_t threshold;
};

using Event = std::variant<monostate, Receipt, Payoff>;

int main() {
    ui_t n;
    cin >> n;

    vector<ui_t> balances_by_person(n + 1, 0U);
    unordered_map<ui_t, ui_t> balances_by_person_after_payoff;

    for (ui_t i = 1; i <= n; ++i) {
        cin >> balances_by_person[i];
    }

    ui_t events_count;
    cin >> events_count;

    vector<Event> events(events_count);

    for (ui_t i = 0; i != events_count; ++i) {
        ui_t event_type;
        cin >> event_type;

        if (event_type == static_cast<ui_t>(EventType::RECEIPT)) {
            ui_t person;
            ui_t balance;
            cin >> person >> balance;

            events[i] = Receipt{person, balance};
        } else {
            ui_t threshold;
            cin >> threshold;

            events[i] = Payoff{threshold};
        }
    }

    for (ui_t i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << balances_by_person[i];
    }
    cout << '\n';
}
