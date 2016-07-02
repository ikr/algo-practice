class RevolvingDoors:
    def turns(self, maze):
        return -1


def at(maze, x, y):
    rowsCount = len(maze)
    columnsCount = len(maze[0])

    if 0 <= x < columnsCount and 0 <= y < rowsCount:
        return maze[y][x]

    return '#'


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

print(at(maze, 2, 4))
