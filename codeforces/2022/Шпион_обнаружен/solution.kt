fun repeatedValue(xs: List<Int>): Int {
    val (a, b, c) = xs;
    if (a == b) {
        return a
    } else if (b == c) {
        return b
    } else {
        assert(a == c)
        return a
    }
}

fun main() {
    repeat(readInt()) {
        val n = readInt()
        val xs = readInts()
        assert(xs.size == n)

        val y = repeatedValue(xs)
        val iy = xs.indexOfFirst { it != y }
        println(iy + 1)
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
