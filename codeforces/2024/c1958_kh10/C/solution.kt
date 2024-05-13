fun mlog2(x: Long): Int {
    return 64 - x.countLeadingZeroBits() - 1
}

fun minCuts(n: Int, k: Long): Int {
    if (k == 0L) return 0
    val l = mlog2(k)
    return n - l + minCuts(l, k xor (1L shl l))
}

fun main() {
    repeat(readInt()) {
        val (n, k) = readLongs()
        println(minCuts(n.toInt(), k))
    }
}

private fun readLn() = readLine()!!

private fun readInt() = readLn().toInt()

private fun readLong() = readLn().toLong()

private fun readStrings() = readLn().split(" ")

private fun readInts() = readStrings().map(String::toInt)

private fun readLongs() = readStrings().map(String::toLong)
