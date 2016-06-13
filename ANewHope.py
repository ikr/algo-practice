class ANewHope:
    def count(self, firstWeek, lastWeek, D):
        return None


def first_wet_index(D, prev_week, week):
    for i in range(len(prev_week)):
        if not is_dry(D, prev_week, week, i):
            return i


def is_dry(D, prev_week, week, day_index):
    shirt = week[day_index]
    hanging_nights = len(prev_week) - prev_week.index(shirt) + day_index
    return hanging_nights >= D
