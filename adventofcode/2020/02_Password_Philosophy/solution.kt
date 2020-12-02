fun main() {
    val ans = generateSequence(::readLine).map(::parseLine).count { isValid(it.first, it.second) }
    println(ans)
}

private fun isValid(policy: Policy, password: String): Boolean {
    val (i, j) = policy.xorIdx
    if (i >= password.length || j >= password.length) return false
    return (password[i] == policy.letter) xor (password[j] == policy.letter)
}

private fun parseLine(line: String): Pair<Policy, String> {
    val g = Regex("^(\\d+)-(\\d+) ([a-z]): ([a-z]+)$").matchEntire(line)!!.groups
    val idxA: Int = g[1]!!.value.toInt() - 1
    val idxB: Int = g[2]!!.value.toInt() - 1
    val letter: Char = g[3]!!.value[0]
    val password: String = g[4]!!.value

    return Policy(idxA to idxB, letter) to password
}

private data class Policy(val xorIdx: Pair<Int, Int>, val letter: Char)

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
