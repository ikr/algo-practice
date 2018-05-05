#!/usr/bin/env python3

def solve(year):
    days = 0
    month = programmers_day_month(year)
    for m in range(1, month):
        days += days_count(year, m)
    return '.'.join((str(256 - days).zfill(2), str(month).zfill(2), str(year)))

def programmers_day_month(year):
    days = 0
    for i in range(1, 13):
        if days + days_count(year, i) < 256:
            days += days_count(year, i)
        else:
            break
    return i

def days_count(year, month):
    if month == 2:
        return february_days_count(year)
    counts_by_month = {1: 31, 3: 31, 4: 30, 5: 31, 6: 30, 7: 31, 8: 31, 9: 30, 10: 31, 11: 30, 12: 31}
    return counts_by_month[month]

def february_days_count(year):
    if year == 1918:
        return 28 - 13
    if year < 1918:
        return 29 if (year % 4 == 0) else 28
    return 29 if (year % 400 == 0 or (year % 4 == 0 and year % 100 !=0)) else 28

if __name__ == '__main__':
    print(solve(1918))
