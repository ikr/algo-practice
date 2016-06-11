class ANewHope:
    def count(self, firstWeek, lastWeek, D):
        return None

def is_dry(prev_week, shirt, week_day, D):
    N = len(prev_week)
    day_worn_prev_week = prev_week.index(shirt) + 1
    drying_days = N - day_worn_prev_week + week_day - 1
    return drying_days >= D


def next_permutation(p):
    k = largest_subordinate_index(p)

    if (k == -1):
        return None

    l = largest_dominating_index(p, k)
    buffer = p[:]
    buffer[k], buffer[l] = buffer[l], buffer[k]
    tail = buffer[k + 1:]
    tail.reverse()

    return buffer[:k + 1] + tail


def largest_subordinate_index(xs):
    if len(xs) < 2:
        return -1

    for i in range(len(xs) - 2, -1, -1):
        if xs[i] < xs[i + 1]:
            return i

    return -1


def largest_dominating_index(xs, subordinate_index):
    for i in range(len(xs) - 1, subordinate_index, -1):
        if xs[subordinate_index] < xs[i]:
            return i
