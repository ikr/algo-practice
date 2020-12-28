import random

n = random.randint(1, 10 ** 5)
m = random.randint(1, n // 2);
print(n, m);
print(" ".join(map(str, random.sample(range(1, n + 1), m))))
