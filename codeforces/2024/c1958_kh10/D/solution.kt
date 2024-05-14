fun sumAtIndices(xs: List<Long>, ii: List<Int>): Long {
    var result = 0L
    for (i in ii) {
        result += xs[i]
    }
    return result
}

fun optimalEffort(xs: List<Long>, ivl: List<Int>): Long {
    assert(ivl.isNotEmpty())

    if (ivl.size % 2 == 0) {
        return 2L * sumAtIndices(xs, ivl)
    }

    val i0 = (0..< ivl.size step 2).maxBy { xs[ivl[it]] }
    return 2L * sumAtIndices(xs, ivl) - xs[ivl[i0]]
}

fun minTotalEffort(xs: List<Long>): Long {
    val ii = mutableListOf<List<Int>>()
    var cur = mutableListOf<Int>()

    xs.forEachIndexed { i, x ->
        if (x > 0L) {
            if (!cur.isEmpty() && cur.last() + 1 != i) {
                ii.add(cur)
                cur = mutableListOf<Int>()
            }
            cur.add(i)
        }
    }

    if (cur.isNotEmpty()) {
        ii.add(cur)
    }

    var result = 0L
    for (ivl in ii) {
        result += optimalEffort(xs, ivl)
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
