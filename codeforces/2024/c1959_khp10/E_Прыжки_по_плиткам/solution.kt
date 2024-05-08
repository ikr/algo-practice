import kotlin.math.abs

fun optimalJumps(xs: String): Pair<Int, List<Int>> {
    val src = xs.first() - 'a'
    val dst = xs.last() - 'a'

    val charIndices = Array(26) { mutableListOf<Int>() }

    for (i in 1 until xs.length - 1) {
        charIndices[xs[i] - 'a'].add(i)
    }

    val indices = mutableListOf(0)
    val delta = if (src == dst) 0 else if (src < dst) 1 else -1

    var i = src
    while (true) {
        while (charIndices[i].isNotEmpty()) {
            val j = charIndices[i].removeAt(charIndices[i].lastIndex)
            indices.add(j)
        }

        if (i == dst && charIndices[i].isEmpty()) break
        i += delta
    }

    indices.add(xs.length - 1)
    return abs(src - dst) to indices
}

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val xs = readLine()!!
        val (loCost, indices) = optimalJumps(xs)
        println("$loCost ${indices.size}")

        indices.forEachIndexed { index, i ->
            print(if (index == 0) "" else " ")
            print(i + 1)
        }
        println()
    }
}
