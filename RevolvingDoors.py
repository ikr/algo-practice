from collections import deque


class RevolvingDoors:
    def turns(self, maze):
        if is_passable(maze):
            return True

        T = {maze: 0}
        Q = deque([maze])

        while len(Q) > 0:
            current = Q.popleft()
            for a in adjacent_mazes(current):
                if a not in T:
                    T[a] = T[current] + 1
                    if is_passable(a):
                        return T[a]
                    Q.append(a)

        return -1


def adjacent_mazes(maze):
    return tuple()


def possible_door_moves(maze, door_coord):
    is_horz = door_orientation(maze, door_coord) == '-'
    all_moves = horz_door_moves(door_coord) if is_horz else vert_door_moves(door_coord)
    start_coord = tile_coord(maze, 'S')

    filtered = filter(lambda mv: can_reach_in_maze(maze, start_coord, mv['from']), all_moves)

    return tuple(filtered)


def door_orientation(maze, door_coord):
    left_neighbour_coord = plus(door_coord, (-1, 0))
    return '-' if at(maze, left_neighbour_coord) == '-' else '|'


################################################################################


def horz_door_moves(door_coord):
    return door_moves(horz_door_moves_tos(door_coord), door_coord)


def vert_door_moves(door_coord):
    return door_moves(vert_door_moves_tos(door_coord), door_coord)


def door_moves(tos, door_coord):
    froms = door_moves_froms(door_coord)
    return coord_pairs_to_door_moves(zip(froms, tos))


def door_moves_froms(door_coord):
    return apply_deltas(((-1, -1), (1, -1), (1, 1), (-1, 1)), door_coord)


def horz_door_moves_tos(door_coord):
    return apply_deltas(((-1, 0), (1, 0), (1, 0), (-1, 0)), door_coord)


def vert_door_moves_tos(door_coord):
    return apply_deltas(((0, -1), (0, -1), (0, 1), (0, 1)), door_coord)


def apply_deltas(deltas, coord):
    return tuple(map(lambda d: plus(coord, d), deltas))


def coord_pairs_to_door_moves(coord_pairs):
    return tuple(map(lambda p: {'from': p[0], 'to': p[1]}, coord_pairs))


################################################################################


def is_passable(maze):
    return can_reach_in_maze(maze, tile_coord(maze, 'S'), tile_coord(maze, 'E'))


def can_reach_in_maze(maze, start_coord, end_coord):
    R = {start_coord: True}
    Q = deque([start_coord])

    while len(Q) > 0:
        current = Q.popleft()
        for a in adjacent_coords(maze, current):
            if a == end_coord:
                return True
            if a not in R:
                R[a] = True
                Q.append(a)

    return False


def adjacent_coords(maze, coord):
    x, y = coord
    result = []

    for delta in (0, -1), (0, 1):
        to_coord = plus(coord, delta)
        if can_move_vertically(at(maze, to_coord)):
            result.append(to_coord)

    for delta in (-1, 0), (1, 0):
        to_coord = plus(coord, delta)
        if can_move_horizontally(at(maze, to_coord)):
            result.append(to_coord)

    return tuple(result)


def at(maze, coord):
    rowsCount = len(maze)
    columnsCount = len(maze[0])
    x, y = coord

    if 0 <= x < columnsCount and 0 <= y < rowsCount:
        return maze[y][x]

    return '#'


def can_move_horizontally(to):
    return can_move({'-': False, '|': True}, to)


def can_move_vertically(to):
    return can_move({'-': True, '|': False}, to)


def can_move(amend_rules, to):
    result = base_move_rules()
    result.update(amend_rules)
    return result[to]


def base_move_rules():
    return {' ': True, '#': False, 'O': False, 'S': False, 'E': True}


def tile_coord(maze, tile):
    for index, row in enumerate(maze):
        if tile in row:
            return maze[index].index(tile), index


def plus(coord1, coord2):
    return coord1[0] + coord2[0], coord1[1] + coord2[1]


m0 = (
    "    ### ",
    "    #E# ",
    "   ## # ",
    "####  ##",
    "# S -O-#",
    "# ###  #",
    "#      #",
    "########"
)

print(possible_door_moves(m0, (5, 4)))

m6 = (
    "#############",
    "#  #|##|#   #",
    "#   O  O    #",
    "# E || || S #",
    "#    O  O   #",
    "#   #|##|#  #",
    "#############"
)

print(possible_door_moves(m6, (4, 2)))

rd = RevolvingDoors()
print(rd.turns(m0))
