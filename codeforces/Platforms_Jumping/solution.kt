fun main() {
    val (n, m, d) = readInts()
    val cs = readInts()
    assert(cs.size == m)

    val ans = solve(n, cs.toMutableList(), d)
    if (ans.isEmpty()) {
        println("NO")
    } else {
        println("YES")
        println(ans.joinToString(" "))
    }
}

private fun solve(n: Int, cs: MutableList<Int>, d: Int): List<Int> {
    val ans = IntArray(n)
    return if (recur(d, ans, cs, 0, 1, n + 1 - cs.sum())) ans.toList() else emptyList()
}

private tailrec fun recur(d: Int, ans: IntArray, cs: MutableList<Int>, i: Int, j: Int, p: Int): Boolean {
    val n = ans.size
    if (cs.isEmpty()) return n + 1 - i <= d

    val c = cs.first()
    cs.removeAt(0)

    if (p - i > d) {
        printPlatform(ans, c, j, i + d)
        return recur(d, ans, cs, i + d + c - 1, j + 1, p + c)
    } else {
        printPlatform(ans, c, j, p)
        return recur(d, ans, cs, p + c - 1, j + 1, p + c)
    }
}

private fun printPlatform(ans: IntArray, c: Int, j: Int, p: Int) {
    for (i in p..p + c - 1) {
        ans[i - 1] = j
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
