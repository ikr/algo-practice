from collections import deque


class TurntableService:
    def calculateTime(favorites):
        return -1


def fully_serving_vertex_sequences(favorites_lists):
    parents = {}
    visited = set()

    initial_range = tuple(range(len(favorites_lists)))
    q = deque((vertex(initial_range, False, initial_range),))

    while len(q) > 0:
        current_vertex = q.popleft()

        for a_vertex in adjacent(current_vertex):
            if not a_vertex in visited:
                parents[a_vertex] = current_vertex

                if all_served(a_vertex):
                    yield sequentialize_children(a_vertex, parents)

                q.append(a_vertex)


def vertex(ttable, do_serve, hungry_indices):
    return {'t': ttable, 's': do_serve, 'h': hungry_indices}


def turn_left(ttable):
    return ttable[1:] + ttable[0:1]


def turn_right(ttable):
    return (ttable[-1],) + ttable[0:-1]


print(vertex((3, 0, 1, 2), False, {0, 1, 2, 3}));
