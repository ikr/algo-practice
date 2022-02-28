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

fun main() {
    val n = readInt()
    val xs = readInts()
    assert(xs.size == n)

    println(maxTeamSizeBruteForce(xs))
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
