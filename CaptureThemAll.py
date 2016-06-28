class CaptureThemAll:
    def fastKnight(self, knight, rook, queen):
        return -1


def position_to_coord(position):
    return ord(position[0]) - ord('a'), int(position[1]) - 1


def adjacent(coord):
    result = []

    for dx, dy in adjacent_deltas():
        x = coord[0] + dx
        y = coord[1] + dy

        if 0 <= x <= 7 and 0 <= x <= 7:
            result.append((x, y))

    return result


def adjacent_deltas():
    return ((-2, -1), (-2, 1), (2, -1), (2, 1), (-1, -2), (1, -2), (-1, 2), (1, 2))

cta = CaptureThemAll()
print(cta.fastKnight('a1', 'b3', 'c5'))

print(adjacent((0, 0)))
print(adjacent((3, 3)))
print(adjacent((7, 4)))
