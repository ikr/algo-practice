class RevolvingDoors:
    def turns(self, maze):
        return -1


def adjacent_coords(maze, coord):
    x, y = coord

    return tuple()


def at(maze, coord):
    rowsCount = len(maze)
    columnsCount = len(maze[0])
    x, y = coord

    if 0 <= x < columnsCount and 0 <= y < rowsCount:
        return maze[y][x]

    return '#'


def can_move_horizontally(to):
    result = base_move_rules()
    result.update({'-': False, '|': True})
    return result[to]


def can_move_vertically(to):
    result = base_move_rules()
    result.update({'-': True, '|': False})
    return result[to]


def base_move_rules():
    return {' ': True, '#': False, 'O': False, 'E': True}


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

print(can_move_vertically('O'))
