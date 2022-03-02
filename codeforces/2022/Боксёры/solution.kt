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

data class NumFreq(val x : Int, val k : Int) {
    init {
        require(x > 0)
        require(k > 0)
    }
}

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
    init {
        require(keepAll >= 0)
        require(decLeft >= 0)
        require(incRight >= 0)
        require(decLeftIncRight >= 0)
    }

    fun best() : Int =
        max(max(keepAll, decLeft), max(incRight, decLeftIncRight))
}

fun maxTeamSize(xs : List<Int>) : Int {
    val fs = sortedNumFreqs(xs)
    val n = fs.size
    val dp = Array<State>(n, { State(0, 0, 0, 0) })

    dp[0] = State(
        keepAll = 1,
        decLeft = if (fs[0].x == 1) 0 else (if (fs[0].k == 1) 1 else 2),
        incRight = if (fs[0].k == 1) 1 else 2,
        decLeftIncRight = when {
            fs[0].x == 1 -> 0
            fs[0].k == 1 -> 0
            fs[0].k == 2 -> 2
            else -> 3
        }
    )

    for (i in 1..(n - 1)) {
        dp[i] = State(
            keepAll = listOf(
                dp[i - 1].keepAll + 1,
                if (dp[i - 1].decLeft == 0) 0 else dp[i - 1].decLeft + 1,
                if (dp[i - 1].incRight == 0) 0 else (
                    if (fs[i - 1].x + 1 == fs[i].x) dp[i - 1].incRight else dp[i - 1].incRight + 1
                ),
                if (dp[i - 1].decLeftIncRight == 0) 0 else (
                    if (fs[i - 1].x + 1 == fs[i].x) dp[i - 1].decLeftIncRight else dp[i - 1].decLeftIncRight + 1
                )
            ).maxOrNull() ?: 0,

            decLeft = listOf(
                if (fs[i - 1].x == fs[i].x - 1) (
                    dp[i - 1].keepAll + (if (fs[i].k == 1) 0 else 1)
                ) else (
                    dp[i - 1].keepAll + (if (fs[i].k == 1) 1 else 2)
                ),
                when {
                    dp[i - 1].decLeft == 0 -> 0
                    fs[i - 1].x == fs[i].x - 1 && fs[i - 1].k > 1 -> (
                        dp[i - 1].decLeft + (if (fs[i].k == 1) 0 else 1)
                    )
                    else -> dp[i - 1].decLeft + (if (fs[i].k == 1) 1 else 2)
                },
                dp[i - 1].incRight + (if (fs[i].k == 1) 0 else 1),
                if (dp[i - 1].decLeftIncRight == 0) 0 else (
                    dp[i - 1].decLeftIncRight + (if (fs[i].k == 1) 0 else 1)
                )
            ).maxOrNull() ?: 0,

            incRight = listOf(
                dp[i - 1].keepAll + (if (fs[i].k == 1) 1 else 2),
                if (dp[i - 1].decLeft == 0) 0 else (
                    dp[i - 1].decLeft + (if (fs[i].k == 1) 1 else 2)
                ),
                if (fs[i - 1].x + 1 == fs[i].x) (
                   dp[i - 1].incRight + 1
                ) else (
                   dp[i - 1].incRight + (if (fs[i].k == 1) 1 else 2)
                ),
                if (dp[i - 1].decLeftIncRight == 0) 0 else (
                    if (fs[i - 1].x + 1 == fs[i].x) (
                        dp[i - 1].decLeftIncRight + 1
                    ) else (
                        dp[i - 1].decLeftIncRight + (if (fs[i].k == 1) 1 else 2)
                    )
                )
            ).maxOrNull() ?: 0,

            decLeftIncRight = if (fs[i].k == 1) 0 else(
                listOf(
                    dp[i - 1].keepAll + (
                        if (fs[i - 1].x == fs[i].x - 1) (
                            if (fs[i].k == 2) 1 else 2
                        ) else (
                            if (fs[i].k == 2) 2 else 3
                        )
                    ),
                    if (dp[i - 1].decLeft == 0) 0 else (
                        dp[i - 1].decLeft + (
                            if (fs[i - 1].x == fs[i].x - 1 && fs[i - 1].k > 1) (
                                if (fs[i].k == 2) 1 else 2
                            ) else (
                                if (fs[i].k == 2) 2 else 3
                            )
                        )
                    )
                ).maxOrNull() ?: 0
            )
        )
    }

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
