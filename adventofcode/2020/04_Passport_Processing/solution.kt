fun main() {
    var ans = 0

    while (true) {
        val values = readPassportBlockValues()
        val tags = values.map { it.first }
        if (tags.isEmpty()) break

        val rem = missingTags(tags.toSet())
        if (rem.isEmpty() || rem == setOf(Tag.cid)) {
            if (values.all(::isValidValue)) ++ans
        }
    }

    println(ans)
}

private fun missingTags(tags: Set<Tag>): Set<Tag> =
    Tag.values().toSet().minus(tags)

private fun readPassportBlockValues(): List<Pair<Tag, String>> {
    val ans = mutableListOf<Pair<Tag, String>>()

    while (true) {
        val line = readLine()
        if (line == null || line == "") break
        ans += readPassportLineValues(line)
    }

    return ans
}

private fun readPassportLineValues(line: String): List<Pair<Tag, String>> =
    line.split(' ').map {
        val (k, v) = it.split(':')
        Tag.valueOf(k) to v
    }

private fun isValidValue(kv: Pair<Tag, String>): Boolean =
    when (kv.first) {
        Tag.byr -> isValidBirthYear(kv.second)
        Tag.iyr -> isValidIssueYear(kv.second)
        Tag.eyr -> isValidExpirationYear(kv.second)
        Tag.hgt -> isValidHeight(kv.second)
        Tag.hcl -> isValidHairColor(kv.second)
        Tag.ecl -> isValidEyeColor(kv.second)
        Tag.pid -> isValidPassportId(kv.second)
        Tag.cid -> true
    }

private fun isValidBirthYear(v: String) =
    isValidYear(v) && v.toInt() in 1920..2002

private fun isValidIssueYear(v: String) =
    isValidYear(v) && v.toInt() in 2010..2020

private fun isValidExpirationYear(v: String) =
    isValidYear(v) && v.toInt() in 2020..2030

private fun isValidYear(v: String) =
    Regex("^[0-9]{4}$").matches(v)

private fun isValidHeight(v: String): Boolean {
    if (!Regex("^[0-9]{2,3}(in|cm)$").matches(v)) return false
    if (v.endsWith("cm")) return isValidHeightCm(v.split("cm").first())
    return isValidHeightIn(v.split("in").first())
}

private fun isValidHeightCm(v: String) =
    v.toInt() in 150..193

private fun isValidHeightIn(v: String) =
    v.toInt() in 59..76

private fun isValidHairColor(v: String) =
    Regex("^#[0-9a-f]{6}$").matches(v)

private fun isValidEyeColor(v: String) =
    EyeColor.values().map { it.name }.contains(v)

private fun isValidPassportId(v: String) =
    Regex("^[0-9]{9}$").matches(v)

private enum class Tag { byr, iyr, eyr, hgt, hcl, ecl, pid, cid }
private enum class EyeColor { amb, blu, brn, gry, grn, hzl, oth }
