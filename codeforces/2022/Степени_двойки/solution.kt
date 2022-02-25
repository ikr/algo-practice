import java.util.SortedMap

fun powersOfTwoFromBinRepr(x : Int) : List<Int> {
    var m = 1
    var curr = x
    val result = mutableListOf<Int>()

    while (curr > 0) {
        if (curr % 2 > 0) {
            result += (curr % 2) * m
        }

        curr /= 2
        m *= 2
    }

    return result
}

fun gatherFreqs(xs : List<Int>) : SortedMap<Int, Int> {
    val result = sortedMapOf<Int, Int>()

    for (x in xs) {
        result.put(x, 1)
    }

    return result
}

fun solve(n : Int, k : Int) : List<Int>? {
    if (n < k) return null
    val fs = gatherFreqs(powersOfTwoFromBinRepr(n));
    if (fs.size > k) return null

    var curr = fs.size
    while (curr < k) {
        val a = fs.lastKey()
        assert(a > 1)
        assert(fs[a]!! > 0)

        fs[a] = fs[a]!! - 1
        if (fs[a] == 0) fs.remove(a)

        if (!fs.containsKey(a / 2)) fs[a / 2] = 0
        fs[a / 2] = fs[a / 2]!! + 2
        ++curr
    }

    val result = mutableListOf<Int>()
    for ((a, b) in fs) {
        repeat(b) {
            result += a
        }
    }
    return result
}

fun main() {
    val (n, k) = readInts()
    val result = solve(n, k)

    if (result == null) {
        println("NO")
    } else {
        println("YES")
        println(result.joinToString(" "))
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
