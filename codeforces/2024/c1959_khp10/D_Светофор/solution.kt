fun minCrossingTime(xs: String, color: Char): Int {
    if (color == 'g') return 0

    val gidx = mutableListOf<Int>();
    xs.forEachIndexed { i, x ->
        if (x == 'g') {
            gidx.add(i)
        }
    }
    gidx.add(xs.length)

    var result = 0
    xs.forEachIndexed { i, x ->
        if (x == color) {
            val jj = gidx.binarySearch(i)
            result = Math.max(result, gidx[-jj - 1] - i)
        }
    }
    return result
}

fun main() {
    repeat(readInt()) {
        val color = readLn().last()
        val xs = readLn()
        println(minCrossingTime(xs + xs, color))
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
