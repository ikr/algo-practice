fun main() {
    var ans = 0

    while (true) {
        val tags = readPassportBlockTags()
        if (tags.isEmpty()) break

        val rem = missingTags(tags)
        if (rem.isEmpty() || rem == setOf(Tag.cid)) ++ans
    }

    println(ans)
}

private fun missingTags(tags: Set<Tag>): Set<Tag> =
    Tag.values().toSet().minus(tags)

private fun readPassportBlockTags(): Set<Tag> {
    val ans = mutableSetOf<Tag>()

    while (true) {
        val line = readLine();
        if (line == null || line == "") break
        ans += readPassportLineTags(line)
    }

    return ans
}

private fun readPassportLineTags(line: String): Set<Tag> =
    line.split(' ').map { it.split(':').first() }.map(Tag::valueOf).toSet()

private enum class Tag { byr, iyr, eyr, hgt, hcl, ecl, pid, cid }
