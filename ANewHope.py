class ANewHope:
    def count(self, firstWeek, lastWeek, D):
        return None


def next_shirt(prev_week, week_so_far, D):
    candidates = list(set(prev_week) - set(week_so_far))
    candidates.sort()

    while candidates:
        shirt = candidates.pop(0)
        if is_dry(prev_week, shirt, len(week_so_far) + 1, D):
            return shirt

    return None


def is_dry(prev_week, shirt, week_day, D):
    N = len(prev_week)
    day_worn_prev_week = prev_week.index(shirt) + 1
    drying_days = N - day_worn_prev_week + week_day - 1
    return drying_days >= D
