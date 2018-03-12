def next_seq(wins):
    if 'A' not in wins:
        return ''
    carry = 1
    result = list(wins)
    for i in range(len(wins)):
        if result[i] == 'A':
            result[i] = 'K'
            break
        result[i] = 'A'
    return ''.join(result)
