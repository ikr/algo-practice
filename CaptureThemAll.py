class CaptureThemAll:
    def fastKnight(self, knight, rook, queen):
        return -1


def coords(position):
    return ord(position[0]) - ord('a'), int(position[1]) - 1


cta = CaptureThemAll()
print(cta.fastKnight('a1', 'b3', 'c5'))

print(coords('a1'))
print(coords('h8'))
