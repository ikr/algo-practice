def partition(xs, l, r):
    p = r
    cursor = l

    for i in range(l, r):
        if xs[i] < xs[p]:
            xs[i], xs[cursor] = xs[cursor], xs[i]
            cursor += 1

    xs[cursor], xs[p] = xs[p], xs[cursor]

    return cursor


l0 = [1,4,1,2,1,9,7,9,1,6]
l1 = l0[:]
p = partition(l1, 0, len(l1) - 1)

print("Partitioned {} at index {} into {}".format(l0, p, l1))
