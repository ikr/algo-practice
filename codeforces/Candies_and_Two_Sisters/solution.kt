fun main() {
    repeat(readInt()) {
        val n = readInt();
        println(countWays(n))
    }
}

private fun countWays(n: Int): Int =
    if (n % 2 == 0) n / 2 - 1 else n / 2

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
