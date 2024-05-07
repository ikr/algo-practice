fun flip(c: Char): Char {
    return if (c.isUpperCase()) c.lowercaseChar() else c.uppercaseChar()
}

fun maxReward(s: String, k: Int): Int {
    val fq = mutableMapOf<Char, Int>()
    for (c in ('a'..'z')) {
        fq[c] = 0;
        fq[c.uppercaseChar()] = 0
    }
    for (c in s) {
        fq[c] = fq[c]!! + 1
    }

    var result = 0
    val rs = mutableListOf<Int>()

    for (x in ('a'..'z')) {
        val f = fq[x]!!
        val y = flip(x)
        val g = fq[y]!!

        val d = Math.min(f, g)
        result += d;
        rs.add(f + g - 2 * d)
    }

    var rk = k
    for (x in rs) {
        val d = Math.min(rk, x / 2)
        result += d
        rk -= d
    }
    return result
}

fun main() {
    repeat(readInt()) {
        val (n, k) = readInts()
        val s = readLn()
        assert(s.length == n)
        println(maxReward(s, k))
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
