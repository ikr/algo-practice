import kotlin.math.max

fun variationOf(xs : List<Int>, opCodes : String) : Set<Int> {
    assert(xs.size == opCodes.length)
    val n = xs.size
    val result = mutableSetOf<Int>()

    for (i in 0..(n - 1)) {
        when (val c = opCodes[i]) {
            '0' -> { result += xs[i] }
            '1' -> { result += xs[i] + 1 }
            '2' -> { result += (if (xs[i] > 1) xs[i] - 1 else xs[i]) }
            else -> error("Impossible opcode $c")
        }
    }

    return result
}

fun maxTeamSizeBruteForce(xs : List<Int>) : Int {
    val n = xs.size
    assert(n <= 16)

    val hi = Integer.parseInt("2".repeat(n), 3)
    var result = 0

    for (x in 0..hi) {
        val opCodes = Integer.toString(x, 3).padStart(n, '0')
        result = max(result, variationOf(xs, opCodes).size)
    }

    return result
}

data class NumFreq(val x : Int, val k : Int)

fun sortedNumFreqs(xs : List<Int>) : List<NumFreq> {
    val m = sortedMapOf<Int, Int>()
    for (x in xs) {
        if (!m.containsKey(x)) m.put(x, 0)
        m.put(x, m[x]!! + 1)
    }

    val result = mutableListOf<NumFreq>()
    for ((k, v) in m) {
        result += NumFreq(k, v)
    }
    return result
}

data class State(
    val keepAll : Int,
    val decLeft : Int,
    val incRight : Int,
    val decLeftIncRight : Int
) {
    fun best() : Int =
        max(max(keepAll, decLeft), max(incRight, decLeftIncRight))
}

fun maxTeamSize(xs : List<Int>) : Int {
    val fs = sortedNumFreqs(xs)
    val n = fs.size
    val dp = Array<State>(n, { State(0, 0, 0, 0) })
    return dp.last().best()
}

fun main() {
    val n = readInt()
    val xs = readInts()
    assert(xs.size == n)

    assert(maxTeamSize(xs) == maxTeamSizeBruteForce(xs), { "WA" })
    println(maxTeamSize(xs))
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
