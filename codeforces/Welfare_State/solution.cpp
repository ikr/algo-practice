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

    vector<ui_t> balances_by_person(n + 1U, 0U);
    unordered_map<ui_t, ui_t> balances_by_person_after_payoff;

    for (ui_t i = 1U; i <= n; ++i) {
        cin >> balances_by_person[i];
    }

    ui_t events_count;
    cin >> events_count;

    vector<Event> events(events_count);

    for (ui_t i = 0U; i != events_count; ++i) {
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

    ui_t max_threshold{0U};

    for (auto it = events.rbegin(); it != events.rend(); ++it) {
        if (holds_alternative<Payoff>(*it)) {
            max_threshold = max(max_threshold, get<Payoff>(*it).threshold);
        } else if (max_threshold) {
            const auto [person, balance] = get<Receipt>(*it);
            *it = Receipt{person, max(balance, max_threshold)};
        }
    }

    unordered_map<ui_t, ui_t> effective_receipts;

    for (const auto ev : events) {
        if (holds_alternative<Receipt>(ev)) {
            const auto [person, balance] = get<Receipt>(ev);
            effective_receipts[person] = balance;
        }
    }

    for (ui_t i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';

        const ui_t ans = effective_receipts.count(i)
                             ? effective_receipts[i]
                             : max(max_threshold, balances_by_person[i]);
        cout << ans;
    }
    cout << '\n';
}
