class RevolvingDoors:
    def turns(self, maze):
        return -1


def adjacent_coords(maze, coord):
    x, y = coord
    result = []

    # for delta in (0, -1), (0, 1):

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


def start_coord(maze):
    for index, row in enumerate(maze):
        if 'S' in row:
            return maze[index].index('S'), index


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

print(plus((1, 2), (3, 4)))
