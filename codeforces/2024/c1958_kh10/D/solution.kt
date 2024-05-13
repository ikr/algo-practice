fun optimalEffort(xs: List<Long>, ivl: List<Int>): Long {
    assert(ivl.isNotEmpty())

    if (ivl.size % 2 == 0) {
        var result = 0L
        for (i in 1 ..< ivl.size step 2) {
            result += 2L * (xs[ivl[i] - 1] + xs[ivl[i]])
        }
        return result
    }

    if (ivl.size == 1) {
        return xs[ivl[0]]
    }

    val i0 = (0 ..< ivl.size step 2).minBy { xs[ivl[it]] }
    var result = xs[ivl[]]
}

fun minTotalEffort(xs: List<Long>): Long {
    val ii = mutableListOf<List<Int>>()
    val cur = mutableListOf<Int>()

    xs.forEachIndexed { i, x ->
        if (x > 0L) {
            if (cur.isEmpty() || cur.last() + 1 == i) {
                cur.add(i)
            } else {
                cur.clear()
                cur.add(i)
            }
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
