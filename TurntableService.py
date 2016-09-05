from collections import deque


class TurntableService:
    def calculateTime(self, favorites):
        favorites_lists = tuple(map(favorites_list, favorites))
        durations = map(duration, fully_serving_vertex_sequences(favorites_lists))
        return min(durations)


def fully_serving_vertex_sequences(favorites_lists):
    parents = {}
    visited = set()

    initial_range = tuple(range(len(favorites_lists)))
    q = deque((vertex(initial_range, False, initial_range),))

    while len(q) > 0:
        current_vertex = q.popleft()

        for a_vertex in adjacent(current_vertex, favorites_lists):
            if not a_vertex in visited:
                visited.add(a_vertex)
                parents[a_vertex] = current_vertex

                if all_served(a_vertex):
                    yield root_to_leaf_sequence(a_vertex, parents)

                q.append(a_vertex)


def duration(vertex_sequence):
    if len(vertex_sequence) == 0:
        return 0

    result = 0

    for v in vertex_sequence:
        result += 1

    return result


def vertex(ttable, do_serve, hungry_indices):
    return {'t': ttable, 's': do_serve, 'h': hungry_indices}


def turn_left(ttable):
    return ttable[1:] + ttable[0:1]


def turn_right(ttable):
    return (ttable[-1],) + ttable[0:-1]


def favorites_list(favorites_string):
    return tuple(set(map(int, favorites_string.split(' '))))


tt0 = tuple(range(4))
idc = set(tt0)
tt1 = turn_left(tt0)
tt2 = turn_left(tt1)

v0 = vertex(tt0, False, idc)
v0_ = vertex(tt0, True, idc)
v1 = vertex(tt1, False, idc)
v2 = vertex(tt2, False, idc)

assert duration(tuple()) == 0
assert duration((v0,)) == 0
assert duration((v0, v1)) == 2
assert duration((v0, v1, v2)) == 3
assert duration((v0, v0_)) == 15
assert duration((v0, v0_, v1)) == 17


ts = TurntableService()
assert ts.calculateTime(("0 2", "1", "0 1")) == 32
assert ts.calculateTime(("0", "0", "0")) == 49
assert ts.calculateTime(("4", "1", "2", "3", "0")) == 50
assert ts.calculateTime(("0 004", "2 3", "0 01", "1 2 3 4", "1 1")) == 35
