fun printInts(xs : List<Int>) {
    println(xs.size)
    println(xs.joinToString(" "))
}

fun solve(xs : List<Int>) : Pair<List<Int>, List<Int>>? {
    if (xs.size == 1) return xs to emptyList()
    if (xs.size == 2) return listOf(xs.first()) to listOf(xs.last())

    val a = mutableListOf<Int>()
    val b = mutableListOf<Int>()

    for (x in xs) {
        if (a.isEmpty() || a.last() != x) {
            a += x
        } else if (b.isEmpty() || b.last() != x) {
            b += x
        } else {
            return null
        }
    }

    return a to b.reversed()
}

fun main() {
    val n = readInt()
    val xs = readInts()
    assert(xs.size == n)

    val result = solve(xs.sorted())
    if (result == null) {
        println("NO")
    } else {
        val (a, b) = result
        println("YES")
        printInts(a)
        printInts(b)
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
