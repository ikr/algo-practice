class TallPeople:
    def getPeople(self, people):
        a = tallest_of_the_shortest(rows(people))
        b = shortest_of_the_tallest(columns(people))
        return a, b


def tallest_of_the_shortest(xs):
    return max(map(min, xs))


def shortest_of_the_tallest(xs):
    return min(map(max, xs))


def columns(people):
    column_indices = range(len(row(people[0])))
    return tuple(map(lambda i: column(i, rows(people)), column_indices))


def column(index, rows):
    return tuple(map(lambda x: x[index], rows))


def rows(people):
    return tuple(map(row, people))


def row(rowText):
    return tuple(map(int, rowText.split(' ')))


tp = TallPeople()
print(tp.getPeople(("9 2 3", "4 8 7")))
print(tp.getPeople(("1 2", "4 5", "3 6")))
print(tp.getPeople(("1 1", "1 1")))
