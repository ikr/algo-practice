import random

# N = 10 ** 9
# M = 2 * 10 ** 5

N = 20
M = 10

n = random.randint(1, N)
m = random.randint(1, min(n, M));
print(n, m);

if (m > 0):
  print(" ".join(map(str, random.sample(range(1, n + 1), m))))
