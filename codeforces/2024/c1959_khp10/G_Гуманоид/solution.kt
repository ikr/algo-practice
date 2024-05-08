import java.util.*

fun queueOf(xs: List<Long>): Queue<Long> {
    val result: Queue<Long> = LinkedList()
    xs.forEach { result.add(it) }
    return result
}

fun strategies(): List<Queue<Long>> {
    return listOf(queueOf(listOf(2, 2, 3)), queueOf(listOf(2, 3, 2)), queueOf(listOf(3, 2, 2)))
}

fun maxYieldUsing(src: List<Long>, h_: Long, mul: Queue<Long>): Long {
    var h = h_
    var result = 0L
    val xs = src.sorted().toMutableList()

    while (xs.isNotEmpty()) {
        val lo = xs[0]
        if (lo >= h) {
            if (mul.isEmpty()) break
            h *= mul.poll().toLong()
            continue
        }

        val index = xs.binarySearch(h)
        val i = if (index >= 0) index else -index - 2

        val x = xs[i]
        h += x / 2
        xs.removeAt(i)
        result++
    }

    return result
}

fun maxYield(src: List<Long>, h: Long): Long {
    var result = 0L
    for (mul in strategies()) {
        result = maxOf(result, maxYieldUsing(src, h, LinkedList(mul)))
    }
    return result
}

fun main() {
    val reader = System.`in`.bufferedReader()

    val t = reader.readLine()!!.toInt()
    repeat(t) {
        val (n, h) = reader.readLine()!!.split(" ").map { it.toLong() }

        val xs = reader.readLine()!!.split(" ").map { it.toLong() }

        println(maxYield(xs, h))
    }
}
