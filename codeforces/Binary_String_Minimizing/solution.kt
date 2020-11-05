fun main() {
    repeat(readInt()) {
        val (n, k) = readInts()
        val bits = readLn().toCharArray()
        assert(bits.size == n)

        minimizeBits(bits, k)
        println(bits.joinToString(""))
    }
}

private fun minimizeBits(bits: CharArray, k: Int) {
    if (bits.size < 2) return

    val bubbleSortComps = bits.size.toLong() * (bits.size.toLong() - 1L) / 2L
    if (k >= bubbleSortComps) {
        bits.sort()
        return
    }

    val yn = sortedSetOf<Int>()

    for (i in 0..(bits.size - 2)) {
        if (bits[i] == '1' && bits[i + 1] == '0') yn += i
    }

    repeat(k) {
        if (yn.isEmpty()) return

        val i = yn.first()
        yn.remove(i)
        swap(bits, i, i + 1)

        if (i > 0 && bits[i - 1] == '1') yn += (i - 1)
        if (i + 1 < bits.size - 1 && bits[i + 2] == '0') yn += (i + 1)
    }
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
