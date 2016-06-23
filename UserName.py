import re


class UserName:
    def newMember(self, existingNames, newName):
        taken = existingNums(newName, existingNames)

        if not taken:
            return newName

        limit = max(taken) + 2
        num = min(set(range(limit)) - taken)
        suffix = '' if num == 0 else str(num)
        return newName + suffix


def existingNums(newName, existingNames):
    result = set()

    for existingName in existingNames:
        parts = parse(existingName)

        if (parts[0] == newName):
            result.add(parts[1])

    return result


def parse(existingName):
    pattern = re.compile('^(.*[a-zA-Z])([0-9]*)$')
    match = pattern.match(existingName)
    return match.group(1), 0 if not match.group(2) else int(match.group(2))
