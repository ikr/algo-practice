fun waitTime(k: Int, m: Int): Int {
    val ro = m / k
    val co = m % k
    return when (ro % 3) {
        2 -> 0
        0 -> k + k - co
        else -> k - co
    }
}

fun main() {
    repeat(readInt()) {
        val (k, m) = readInts()
        println(waitTime(k, m))
    }
}

private fun readLn() = readLine()!!

private fun readInt() = readLn().toInt()

private fun readLong() = readLn().toLong()

private fun readStrings() = readLn().split(" ")

private fun readInts() = readStrings().map(String::toInt)

private fun readLongs() = readStrings().map(String::toLong)
