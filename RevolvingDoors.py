from collections import deque


class RevolvingDoors:
    def turns(self, maze):
        return -1


def search_turns(original_maze):
    T = {original_maze: -1}
    Q = deque([original_maze])

    while len(Q) > 0:
        current = Q.popleft()


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


maze = (
    "    ### ",
    "    #E# ",
    "   ## # ",
    "####  ##",
    "# S -O-#",
    "# ###  #",
    "#      #",
    "########"
)

print(is_passable(maze))
