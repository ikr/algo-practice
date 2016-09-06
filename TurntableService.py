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
    q = deque((vertex(initial_range, False, set(initial_range)),))

    while len(q) > 0:
        current_vertex = q.popleft()

        for a_vertex in adjacent(current_vertex, favorites_lists):
            if not hashify(a_vertex) in visited:
                visited.add(hashify(a_vertex))
                parents[hashify(a_vertex)] = current_vertex

                if all_served(a_vertex):
                    yield root_to_leaf_sequence(a_vertex, parents)

                q.append(a_vertex)


def root_to_leaf_sequence(v, parents):
    result = [v]
    current = v

    while hashify(current) in parents:
        result.insert(0, parents[hashify(current)])
        current = parents[hashify(current)]

    return tuple(result)


def all_served(v):
    return len(v['h']) == 0


def hashify(v):
    return (v['t'], v['s'], tuple(v['h']))


def duration(vertex_sequence):
    assert len(vertex_sequence) > 1
    assert not vertex_sequence[0]['s']

    result = 0

    for u, v in zip(vertex_sequence, vertex_sequence[1:]):
        assert not (u['s'] and v['s'])

        if v['s']:
            result += 15
        else:
            result += (2 if u['s'] or result == 0 else 1)

    return result


def adjacent(v, favorites_lists):
    v_l = vertex(turn_left(v['t']), False, v['h'])
    v_r = vertex(turn_right(v['t']), False, v['h'])

    if v['s']:
        return (v_l, v_r)

    result = []

    if can_serve(v['t'], favorites_lists, v['h']):
        result.append(vertex(v['t'], True, serve(v['t'], favorites_lists, v['h'])))

    if v != v_l:
        result.append(v_l)

    if v_r != v_l:
        result.append(v_r)

    return tuple(result)


def can_serve(ttable, favorites_lists, hungry_indices):
    return serve(ttable, favorites_lists, hungry_indices) != hungry_indices


def serve(ttable, favorites_lists, hungry_indices):
    result = hungry_indices.copy()

    for i, entree in zip(range(len(ttable)), ttable):
        if entree in favorites_lists[i] and i in result:
            result.remove(i)

    return result


def vertex(ttable, do_serve, hungry_indices):
    return {'t': ttable, 's': do_serve, 'h': hungry_indices}


def turn_left(ttable):
    return ttable[1:] + ttable[0:1]


def turn_right(ttable):
    return (ttable[-1],) + ttable[0:-1]


def favorites_list(favorites_string):
    return tuple(set(map(int, favorites_string.split(' '))))

####################################################################################################

import unittest

class TestServe(unittest.TestCase):
    def test_is_identical_when_cant_serve(self):
        result = serve((0, 1), ((1,), (0,)), {0, 1})
        expected = {0, 1}
        self.assertEqual(result, expected)

    def test_serves_one(self):
        result = serve((0, 1, 2), ((2,), (0, 1, 2), (0,)), {0, 1, 2})
        expected = {0, 2}
        self.assertEqual(result, expected)

    def test_does_nothing_if_person_is_already_served(self):
        result = serve((0, 1, 2), ((2,), (1,), (0,)), {0})
        expected = {0}
        self.assertEqual(result, expected)

class TestAdjacentOnTurntableOfSize3(unittest.TestCase):
    def setUp(self):
        self.v0 = vertex((0, 1, 2), False, {0, 1, 2})
        self.v0_ = vertex((0, 1, 2), True, {2})
        self.v1 = vertex((1, 2, 0), False, {0, 1, 2})
        self.v2 = vertex((2, 0, 1), False, {0, 1, 2})

    def test_when_servable(self):
        result = adjacent(self.v0, ((0, 2), (1,), (0, 1)))
        expected = (self.v0_, self.v1, self.v2)
        self.assertEqual(result, expected)

    def test_when_not_servable(self):
        result = adjacent(self.v0, ((2,), (0,), (1,)))
        expected = (self.v1, self.v2)
        self.assertEqual(result, expected)

    def test_after_serving(self):
        result = adjacent(self.v0_, ((0, 1, 2), (0, 1, 2), (0, 1, 2)))
        expected = ({'t': (1, 2, 0), 's': False, 'h': {2}}, {'t': (2, 0, 1), 's': False, 'h': {2}})
        self.assertEqual(result, expected)

class TestAdjacentOnTurntableOfSize2(unittest.TestCase):
    def setUp(self):
        self.w0 = vertex((0, 1), False, {0, 1})
        self.w0_ = vertex((0, 1), True, set())
        self.w1 = vertex((1, 0), False, {0, 1})

    def test_when_servable(self):
       self.assertEqual(adjacent(self.w0, ((0, 1), (0, 1))), (self.w0_, self.w1))

    def test_when_not_servable(self):
        self.assertEqual(adjacent(self.w0, ((1,), (0,))), (self.w1,))

class TestAdjacentOnTurntableOfSize1(unittest.TestCase):
    def test_for_sure_serving(self):
        u0 = vertex((0,), False, {0})
        u0_ = vertex((0,), True, set())
        self.assertEqual(adjacent(u0, ((0,),)), (u0_,))

ts = TurntableService()
assert ts.calculateTime(("0 2", "1", "0 1")) == 32
# assert ts.calculateTime(("0", "0", "0")) == 49
# assert ts.calculateTime(("4", "1", "2", "3", "0")) == 50
# assert ts.calculateTime(("0 004", "2 3", "0 01", "1 2 3 4", "1 1")) == 35

unittest.main()
