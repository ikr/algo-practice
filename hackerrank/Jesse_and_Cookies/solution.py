import heapq
import fileinput


def sweetness_increases_count(min_required_sweetness, cookies):
    if len(cookies) == 0:
        return 0 if min_required_sweetness == 0 else -1

    cookies_heap = list(cookies)
    heapq.heapify(cookies_heap)
    result = 0

    while cookies_heap[0] < min_required_sweetness and len(cookies_heap) >= 2:
        combine_two_least_sweet_cookies(cookies_heap)
        result += 1

    return result if cookies_heap[0] >= min_required_sweetness else -1


def combine_two_least_sweet_cookies(cookies_heap):
    min_sweetness = heapq.heappop(cookies_heap)
    second_min_sweetness = heapq.heappop(cookies_heap)
    heapq.heappush(cookies_heap, combined_cookie_sweetness(min_sweetness, second_min_sweetness))


def combined_cookie_sweetness(min_sweetness, second_min_sweetness):
    return min_sweetness + 2 * second_min_sweetness


"""IO"""


def main():
    input = tuple(map(lambda x: tuple(x.strip().split(' ')),fileinput.input()))
    min_required_sweetness = int(input[0][1])
    cookies = tuple(map(int, input[1]))
    print(sweetness_increases_count(min_required_sweetness, cookies))


if __name__ == '__main__':
    main()
