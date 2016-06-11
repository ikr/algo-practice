class ANewHope:
    def count(self, firstWeek, lastWeek, D):
        return None


def next_permutation(p, D):
    k = largest_subordinate_index(p)

    if k == -1:
        return None

    l = largest_dominating_index(p, k)

    buffer = p[:]
    buffer[k], buffer[l] = buffer[l], buffer[k]
    tail = buffer[k + 1:]
    tail.reverse()
    result = buffer[:k + 1] + tail

    if is_dry(p, k, l, D) and is_dry(p, l, k, D):
        return result
    else:
        return next_permutation(result, D)


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


def is_dry(week, old_index, new_index, D):
    N = len(week)
    drying_days = N - 1 - old_index + new_index
    return drying_days >= D
