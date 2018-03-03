class RangeEncoding:
    # Tuple Int -> Int
    def minRanges(self, arr):
        ranges_count = 0
        prev = -1

        for x in arr:
            if x != prev + 1:
                ranges_count += 1

            prev = x

        return ranges_count


print(RangeEncoding().minRanges((1,2,3,4,5,6,7,8,9,10)), 1)
print(RangeEncoding().minRanges((1,6,10,20,32,49)), 6)
