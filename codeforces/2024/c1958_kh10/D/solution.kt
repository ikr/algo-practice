fun minTotalEffort(xs: List<Long>): Long {
    val n = xs.size
    val pis = (1 ..< n).filter { xs[it - 1] > 0L && xs[it] > 0L }.toMutableList()
    pis.sortBy { 2L * (xs[it - 1] + xs[it]) }

    val r = (0 ..< n).toMutableSet()

    var result = 0L

    for (i1 in pis) {
        val i0 = i1 - 1
        if (r.contains(i0) && r.contains(i1)) {
            result += 2L * (xs[i0] + xs[i1])
            r.remove(i0)
            r.remove(i1)
        }
    }

    xs.forEachIndexed { i, x ->
        if (x > 0 && r.contains(i)) {
            result += x
            r.remove(i)
        }
    }

    return result
}

fun main() {
    val result = mutableListOf<Long>()

    repeat(readInt()) {
        val n = readInt()
        val xs = readLongs()
        assert(xs.size == n)

        result.add(minTotalEffort(xs))
    }

    println(result.joinToString("\n"))
}

private fun readLn() = readLine()!!

private fun readInt() = readLn().toInt()

private fun readLong() = readLn().toLong()

private fun readStrings() = readLn().split(" ")

private fun readInts() = readStrings().map(String::toInt)

private fun readLongs() = readStrings().map(String::toLong)
