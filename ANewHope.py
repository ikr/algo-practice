class ANewHope:
    def count(self, firstWeek, lastWeek, D):
        return refine_count(D, firstWeek, lastWeek, 1 if firstWeek == lastWeek else 2)


def refine_count(D, prev_week, week, current_count):
    if prev_week == week:
        return current_count

    middle_week = week[:]
    swaps_count = 0

    while True:
        first_wet = first_wet_index(D, prev_week, middle_week)

        if first_wet == -1:
            return refine_count(D, middle_week, week, current_count + 1)

        dry = dry_index(D, prev_week, middle_week, swaps_count)
        middle_week[first_wet], middle_week[dry] = middle_week[dry], middle_week[first_wet]
        swaps_count += 1


def dry_index(D, prev_week, week, offset):
    N = len(prev_week)
    return week.index(prev_week[N - D - offset])


def first_wet_index(D, prev_week, week):
    for i in range(len(prev_week)):
        if not is_dry(D, prev_week, week, i):
            return i

    return -1


def is_dry(D, prev_week, week, day_index):
    shirt = week[day_index]
    hanging_nights = len(prev_week) - prev_week.index(shirt) + day_index
    return hanging_nights >= D
