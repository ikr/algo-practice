import java.lang.Math

fun main() {
    val n = readInt()
    val xs = readInts().sorted()
    val result = xs.windowed(2, 2).map { Math.abs(it[0] - it[1]) }.sum()
    println(result)
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
