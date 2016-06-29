from collections import deque


class CaptureThemAll:
    def fastKnight(self, knight, rook, queen):
        G = {position_to_coord(knight): vertex(0, None)}
        Q = deque([position_to_coord(knight)])

        while len(Q) > 0:
            current = Q.popleft()
            for a in adjacent(current):
                if not a in G:
                    G[a] = vertex(G[current]['d'] + 1, current)
                    Q.append(a)

        return -1


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


def position_to_coord(position):
    return ord(position[0]) - ord('a'), int(position[1]) - 1


def vertex(distance, parent):
    return {'d': distance, 'p': parent}


cta = CaptureThemAll()
print(cta.fastKnight('a1', 'b3', 'c5'))
