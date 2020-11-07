fun main() {
    repeat(readInt()) {
        val (n, k) = readLongs()
        val bits = readLn().toCharArray()
        assert(bits.size.toLong() == n)

        minimizeBits(bits, k)
        println(bits.joinToString(""))
    }
}

private fun minimizeBits(bits: CharArray, k: Long) {
    if (bits.size < 2) return

    var (lo, hi) = onesRange(bits)
    if (lo == -1) return

    recur(bits, k, lo, hi)
}

private fun recur(bits: CharArray, k: Long, lo: Int, hi: Int) {
    if (hi == bits.size - 1 || k == 0L) return

    val n = hi - lo + 1
    if (k <= n) {
        swap(bits, hi - k.toInt() + 1, hi + 1)
        return
    }

    swap(bits, lo, hi + 1)
    recur(bits, k - n, lo + 1, lastIndexOfOne(bits, hi + 1))
}

private fun onesRange(bits: CharArray): Pair<Int, Int> {
    val lo = bits.indexOf('1')
    if (lo == -1) return -1 to -1
    return lo to lastIndexOfOne(bits, lo)
}

private fun lastIndexOfOne(bits: CharArray, after: Int): Int {
    var i = after
    while (i < bits.size - 1 && bits[i + 1] == '1') ++i
    return i
}

private fun swap(xs: CharArray, i: Int, j: Int) {
    val x = xs[i]
    xs[i] = xs[j]
    xs[j] = x
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
