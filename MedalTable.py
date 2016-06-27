class MedalTable:
    def generate(self, results):
        r_data = rows_data(medals_by_country(results))
        r_data.sort(key = sort_key)
        return rows(r_data)


def medals_by_country(results):
    storage = {}
    def inc_value(country, subkey):
        if not country in storage:
            storage[country] = {'gold': 0, 'silver': 0, 'bronze': 0}
        storage[country][subkey] += 1

    for result in results:
        gold, silver, bronze = result.split(' ')
        inc_value(gold, 'gold')
        inc_value(silver, 'silver')
        inc_value(bronze, 'bronze')

    return storage


def rows_data(storage):
    result = []

    for country in storage.keys():
        c = storage[country]
        r = (country, c['gold'], c['silver'], c['bronze'])
        result.append(r)

    return result


def sort_key(r_data):
    counts_format = '{:02d}{:02d}{:02d}'
    counts = counts_format.format(50 - r_data[1], 50 - r_data[2], 50 - r_data[3])
    return counts + r_data[0]


def rows(rows_data):
    return tuple(map(row, rows_data))


def row(row_data):
    return ' '.join(map(str, row_data))


mt = MedalTable()
results = ("ITA JPN AUS", "KOR TPE UKR", "KOR KOR GBR", "KOR CHN TPE")
print(mt.generate(results))
