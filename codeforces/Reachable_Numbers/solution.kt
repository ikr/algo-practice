fun main() {
    val n = readInt()
    println(allNums(n).size)
}

private fun allNums(seed: Int): Set<Int> {
    var x = seed
    val ans = mutableSetOf(seed)
    while (nextNum(x) !in ans) {
        x = nextNum(x)
        ans += x
    }
    return ans
}

private fun nextNum(x: Int): Int =
    if ((x + 1) % 10 == 0) dropTrailingZeroes(x + 1) else x + 1

private fun dropTrailingZeroes(x: Int): Int {
    var ans = x
    while (ans % 10 == 0) ans = ans / 10
    return ans
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
