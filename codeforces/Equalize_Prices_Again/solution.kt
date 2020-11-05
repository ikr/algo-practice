fun main() {
    repeat(readInt()) {
        val n = readInt()
        val xs = readInts()
        val total = xs.sum();

        val ans = if (total % n == 0) total / n else total / n + 1
        println(ans)
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
