fun isPossible(xs: List<Int>): Boolean {
    val openingIndices = MutableList(xs.size) { mutableListOf<Int>() }

    for (i in xs.indices) {
        val j = i + xs[i]
        if (j < xs.size) openingIndices[j].add(i)
    }

    val canBeLast = MutableList(xs.size) { false }

    for (i in 1 until xs.size) {
        val k = i - xs[i] - 1
        if (k == -1 || (k >= 0 && canBeLast[k])) {
            canBeLast[i] = true
            continue
        }

        for (j in openingIndices[i]) {
            if (j == 0 || canBeLast[j - 1]) {
                canBeLast[i] = true
                break
            }
        }
    }

    return canBeLast.last()
}

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val n = readLine()!!.toInt()
        val xs = readLine()!!.split(" ").map { it.toInt() }

        println(if (isPossible(xs)) "YES" else "NO")
    }
}
