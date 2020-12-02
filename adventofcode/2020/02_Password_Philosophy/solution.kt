fun main() {
    val ans = generateSequence(::readLine).map(::parseLine).count { isValid(it.first, it.second) }
    println(ans)
}

private fun isValid(policy: Policy, password: String): Boolean {
    val freq = password.count { it == policy.letter }
    val (lo, hi) = policy.freqRange
    return lo <= freq && freq <= hi
}

private fun parseLine(line: String): Pair<Policy, String> {
    val g = Regex("^(\\d+)-(\\d+) ([a-z]): ([a-z]+)$").matchEntire(line)!!.groups
    val freqFrom: Int = g[1]!!.value.toInt()
    val freqTo: Int = g[2]!!.value.toInt()
    val letter: Char = g[3]!!.value[0]
    val password: String = g[4]!!.value

    return Policy(freqFrom to freqTo, letter) to password
}

private data class Policy(val freqRange: Pair<Int, Int>, val letter: Char) {
    init { require(freqRange.first <= freqRange.second) }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
