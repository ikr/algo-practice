from fileinput import input


prefix_counts = {}


def add(word):
    for i in range(1, len(word) + 1):
        inc_count(word[:i])


def inc_count(prefix):
    if prefix in prefix_counts:
        prefix_counts[prefix] += 1
    else:
        prefix_counts[prefix] = 1


input_lines = tuple(map(lambda x: x.strip().split(' '), input()))
for cmd, name in input_lines[1:]:
    if cmd == 'add':
        add(name)
        print(prefix_counts)
    else:
        print(prefix_counts[name] if name in prefix_counts else 0)
