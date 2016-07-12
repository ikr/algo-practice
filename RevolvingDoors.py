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
    result = []

    for door_coord in door_coords(maze):
        for door_move in unique_door_moves(possible_door_moves(maze, door_coord)):
            result.append(make_a_move(maze, door_coord, door_move['to']))

    return tuple(result)


def possible_door_moves(maze, door_coord):
    is_horz = door_orientation(maze, door_coord) == '-'
    all_moves = horz_door_moves(door_coord) if is_horz else vert_door_moves(door_coord)
    start_coord = tile_coord(maze, 'S')

    filtered = filter(lambda mv: can_reach_in_maze(maze, start_coord, mv['from']), all_moves)

    return tuple(filtered)


def unique_door_moves(door_moves):
    result = []
    tos = set()

    for door_move in door_moves:
        if not door_move['to'] in tos:
            result.append(door_move)
            tos.add(door_move['to'])

    return tuple(result)


def door_coords(maze):
    result = []

    for y, row in enumerate(maze):
        for x, tile in enumerate(row):
            if tile == 'O':
                result.append((x, y))

    return tuple(result)


################################################################################


def make_a_move(maze, door_coord, to_coord):
    return new_start(turn_door(maze, door_coord), to_coord)


def new_start(maze, coord):
    old_coord = tile_coord(maze, 'S')
    result = maze

    if old_coord:
        result = set_tile(result, ' ', old_coord)

    return set_tile(result, 'S', coord)


def turn_door(maze, door_coord):
    result = maze

    if door_orientation(maze, door_coord) == '-':
        result = set_tile(result, ' ', plus(door_coord, (-1, 0)))
        result = set_tile(result, ' ', plus(door_coord, (1, 0)))
        result = set_tile(result, '|', plus(door_coord, (0, -1)))
        result = set_tile(result, '|', plus(door_coord, (0, 1)))
    else:
        result = set_tile(result, ' ', plus(door_coord, (0, -1)))
        result = set_tile(result, ' ', plus(door_coord, (0, 1)))
        result = set_tile(result, '-', plus(door_coord, (-1, 0)))
        result = set_tile(result, '-', plus(door_coord, (1, 0)))

    return result


def set_tile(maze, tile, coord):
    x, y = coord
    row = maze[y][:x] + tile + maze[y][x + 1:]
    return maze[:y] + (row, ) + maze[y + 1:]


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

    for delta in (0, -1), (0, 1), (-1, 0), (1, 0):
        to_coord = plus(coord, delta)
        if can_move(at(maze, to_coord)):
            result.append(to_coord)

    return tuple(result)


def at(maze, coord):
    rowsCount = len(maze)
    columnsCount = len(maze[0])
    x, y = coord

    if 0 <= x < columnsCount and 0 <= y < rowsCount:
        return maze[y][x]

    return '#'


def can_move(to):
    mv = {' ': True, 'E': True, 'S': False, '#': False, 'O': False, '-': False, '|': False}
    return mv[to]


def tile_coord(maze, tile):
    for index, row in enumerate(maze):
        if tile in row:
            return maze[index].index(tile), index


def plus(coord1, coord2):
    return coord1[0] + coord2[0], coord1[1] + coord2[1]


################################################################################


def print_mazes(mazes):
    for maze in mazes:
        print_maze(maze)


def print_maze(maze):
    return print('\n'.join(maze))


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

print_maze(m0)
print_mazes(adjacent_mazes(m0))

m2 = (
    " |  |  |     |  |  |  |  |  | ",
    " O  O EO -O- O  O  O  O  OS O ",
    " |  |  |     |  |  |  |  |  | "
)

print_maze(m2)
print_mazes(adjacent_mazes(m2))

m3 = (
    "###########",
    "#    #    #",
    "#  S | E  #",
    "#    O    #",
    "#    |    #",
    "#         #",
    "###########"
)

print_maze(m3)
print_mazes(adjacent_mazes(m3))

m6 = (
    "#############",
    "#  #|##|#   #",
    "#   O  O    #",
    "# E || || S #",
    "#    O  O   #",
    "#   #|##|#  #",
    "#############"
)

print_maze(m6)
print_mazes(adjacent_mazes(m6))
print_mazes(adjacent_mazes(adjacent_mazes(m6)[0]))

rd = RevolvingDoors()
print(rd.turns(m6))
