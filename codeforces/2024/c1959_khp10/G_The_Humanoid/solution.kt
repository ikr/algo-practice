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
    val pairComparator = compareBy<Pair<Long, Int>> { it.first }.thenBy { it.second }
    val xs = TreeSet(pairComparator)
    for (x in src) xs.add(x to xs.size)

    while (xs.isNotEmpty()) {
        val lo = xs.first().first
        if (lo >= h) {
            if (mul.isEmpty()) break
            h *= mul.poll().toLong()
            continue
        }

        val k = xs.lower(h to 0)
        assert(k != null)

        val x = k.first
        if (x <= h) {
            h += x / 2
            xs.remove(k)
            result++
        } else {
            break
        }
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
        assert(xs.size.toLong() == n)
        println(maxYield(xs, h))
    }
}
