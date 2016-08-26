class TurntableService:
    def calculateTime(favorites):
        return -1


def vertex(ttable, do_serve, hungry_indices):
    return {'t': ttable, 's': do_serve, 'h': hungry_indices}


def turn_left(ttable):
    return ttable[1:] + ttable[0:1]


def turn_right(ttable):
    return (ttable[-1],) + ttable[0:-1]


print(vertex((3, 0, 1, 2), False, {0, 1, 2, 3}));
